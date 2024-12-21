#include "OpenSSLUtil.hpp"

#include <stdexcept>
#include <vector>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

namespace common
{
    auto OpenSSLUtil::deriveKey(const std::string& password, unsigned char key[32], unsigned char salt[16]) -> void
    {
        EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, reinterpret_cast<const unsigned char*>(password.c_str()), static_cast<int>(password.size()), 1, key, nullptr);
    }

    auto OpenSSLUtil::encryptAES256CBC(const std::string& plaintext, const std::string& password, unsigned char salt[16]) -> std::vector<unsigned char>
    {
        unsigned char key[32];
        RAND_bytes(salt, sizeof(salt));
        deriveKey(password, key, salt);

        unsigned char iv[AES_BLOCK_SIZE];
        RAND_bytes(iv, AES_BLOCK_SIZE);

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        int len, ciphertext_len = 0;
        std::vector<unsigned char> ciphertext(plaintext.size() + AES_BLOCK_SIZE);

        EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);
        EVP_EncryptUpdate(ctx, ciphertext.data(), &len, reinterpret_cast<const unsigned char*>(plaintext.data()), static_cast<int>(plaintext.size()));
        ciphertext_len += len;

        EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
        ciphertext_len += len;
        ciphertext.resize(ciphertext_len);

        EVP_CIPHER_CTX_free(ctx);

        std::vector<unsigned char> result;
        result.insert(result.end(), iv, iv + AES_BLOCK_SIZE);
        result.insert(result.end(), ciphertext.begin(), ciphertext.end());
        return result;
    }

    auto OpenSSLUtil::decryptAES256CBC(const std::vector<unsigned char>& ciphertext, const std::string& password, unsigned char salt[16]) -> std::string
    {
        if (ciphertext.size() < 16) throw std::runtime_error("Invalid ciphertext length");

        unsigned char key[32];
        deriveKey(password, key, salt);

        unsigned char iv[AES_BLOCK_SIZE];
        std::copy_n(ciphertext.begin(), 16, iv);

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        int len, plaintext_len = 0;
        std::vector<unsigned char> plaintext(ciphertext.size());

        EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);
        EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data() + 16, static_cast<int>(ciphertext.size() - 16));
        plaintext_len += len;

        int final_len;
        EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &final_len);
        plaintext_len += final_len;

        EVP_CIPHER_CTX_free(ctx);
        return {reinterpret_cast<const char*>(plaintext.data()), static_cast<std::string::size_type>(plaintext_len)};
    }
}
