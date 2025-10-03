#pragma once

#include <string>
#include <vector>

namespace common
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
}
