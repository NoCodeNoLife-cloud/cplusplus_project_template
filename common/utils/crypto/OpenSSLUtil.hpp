#pragma once
#include <string>
#include <vector>

namespace common {
class OpenSSLUtil {
 public:
  static auto deriveKey(const std::string& password, unsigned char key[32],
                        unsigned char salt[16]) -> void;
  static auto encryptAES256CBC(const std::string& plaintext,
                               const std::string& password,
                               unsigned char salt[16])
      -> std::vector<unsigned char>;
  static auto decryptAES256CBC(const std::vector<unsigned char>& ciphertext,
                               const std::string& password,
                               unsigned char salt[16]) -> std::string;
};
}  // namespace common
