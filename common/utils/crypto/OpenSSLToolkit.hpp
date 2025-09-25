#pragma once
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#include <stdexcept>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

namespace fox
{
    /// @brief Utility class for OpenSSL cryptographic operations.
    /// This class provides methods for key derivation, encryption, and decryption
    /// using OpenSSL's AES-256-CBC algorithm with PBKDF2 key derivation.
    class OpenSSLToolkit
    {
    public:
        OpenSSLToolkit() = delete;

        /// @brief Derives a key from the given password and salt using PBKDF2.
        /// @param password The password to derive the key from.
        /// @param key The output key buffer (32 bytes for AES-256).
        /// @param salt The salt to use in key derivation (16 bytes).
        static auto deriveKey(const std::string& password, unsigned char key[32],
                              unsigned char salt[16]) noexcept -> void;

        /// @brief Encrypts the given plaintext using AES-256-CBC with a key derived from the password.
        /// @param plaintext The plaintext to encrypt.
        /// @param password The password used to derive the encryption key.
        /// @param salt The salt used for key derivation (16 bytes).
        /// @return The encrypted ciphertext as a vector of bytes.
        /// @throws std::runtime_error If encryption fails.
        [[nodiscard]] static auto encryptAES256CBC(const std::string& plaintext, const std::string& password,
                                                   unsigned char salt[16]) -> std::vector<unsigned char>;

        /// @brief Decrypts the given ciphertext using AES-256-CBC with a key derived from the password.
        /// @param ciphertext The ciphertext to decrypt.
        /// @param password The password used to derive the decryption key.
        /// @param salt The salt used for key derivation (16 bytes).
        /// @return The decrypted plaintext as a string.
        /// @throws std::runtime_error If decryption fails or ciphertext is invalid.
        [[nodiscard]] static auto decryptAES256CBC(const std::vector<unsigned char>& ciphertext,
                                                   const std::string& password,
                                                   unsigned char salt[16]) -> std::string;
    };

    inline auto OpenSSLToolkit::deriveKey(const std::string& password, unsigned char key[32],
                                       unsigned char salt[16]) noexcept -> void
    {
        EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt,
                       reinterpret_cast<const unsigned char*>(password.c_str()),
                       static_cast<int32_t>(password.size()), 1, key, nullptr);
    }

    inline auto OpenSSLToolkit::encryptAES256CBC(const std::string& plaintext, const std::string& password,
                                              unsigned char salt[16]) -> std::vector<unsigned char>
    {
        unsigned char key[32];
        RAND_bytes(salt, 16);
        deriveKey(password, key, salt);

        unsigned char iv[AES_BLOCK_SIZE];
        RAND_bytes(iv, AES_BLOCK_SIZE);

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        if (!ctx)
        {
            throw std::runtime_error("Failed to create cipher context");
        }

        // Ensure proper cleanup of context
        std::unique_ptr<EVP_CIPHER_CTX, decltype(&EVP_CIPHER_CTX_free)> ctx_guard(ctx, EVP_CIPHER_CTX_free);

        int32_t len, ciphertext_len = 0;
        std::vector<unsigned char> ciphertext(plaintext.size() + AES_BLOCK_SIZE);

        if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv) != 1)
        {
            throw std::runtime_error("Failed to initialize encryption");
        }

        if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len,
                              reinterpret_cast<const unsigned char*>(plaintext.data()),
                              static_cast<int32_t>(plaintext.size())) != 1)
        {
            throw std::runtime_error("Failed to encrypt data");
        }
        ciphertext_len += len;

        if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len) != 1)
        {
            throw std::runtime_error("Failed to finalize encryption");
        }
        ciphertext_len += len;
        ciphertext.resize(ciphertext_len);

        std::vector<unsigned char> result;
        result.reserve(AES_BLOCK_SIZE + ciphertext.size());
        result.insert(result.end(), iv, iv + AES_BLOCK_SIZE);
        result.insert(result.end(), ciphertext.begin(), ciphertext.end());
        return result;
    }

    inline auto OpenSSLToolkit::decryptAES256CBC(const std::vector<unsigned char>& ciphertext, const std::string& password,
                                              unsigned char salt[16]) -> std::string
    {
        if (ciphertext.size() < AES_BLOCK_SIZE)
            throw std::runtime_error("Invalid ciphertext length");

        unsigned char key[32];
        deriveKey(password, key, salt);

        unsigned char iv[AES_BLOCK_SIZE];
        std::copy_n(ciphertext.begin(), AES_BLOCK_SIZE, iv);

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        if (!ctx)
        {
            throw std::runtime_error("Failed to create cipher context");
        }

        // Ensure proper cleanup of context
        std::unique_ptr<EVP_CIPHER_CTX, decltype(&EVP_CIPHER_CTX_free)> ctx_guard(ctx, EVP_CIPHER_CTX_free);

        int32_t len, plaintext_len = 0;
        std::vector<unsigned char> plaintext(ciphertext.size());

        if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv) != 1)
        {
            throw std::runtime_error("Failed to initialize decryption");
        }

        if (EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data() + AES_BLOCK_SIZE,
                              static_cast<int32_t>(ciphertext.size() - AES_BLOCK_SIZE)) != 1)
        {
            throw std::runtime_error("Failed to decrypt data");
        }
        plaintext_len += len;

        int32_t final_len;
        if (EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &final_len) != 1)
        {
            throw std::runtime_error("Failed to finalize decryption");
        }
        plaintext_len += final_len;

        return {
            reinterpret_cast<const char*>(plaintext.data()), static_cast<std::string::size_type>(plaintext_len)
        };
    }
}
