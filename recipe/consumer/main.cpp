#include <azure/storage/common/crypt.hpp>
#include <azure/core/base64.hpp>
#include <iostream>
#include <string>
int main() {
    // Known-answer vector from the SDK's crypt_functions_test.cpp.
    const std::string data = "Hello Azure!";
    const auto* bytes = reinterpret_cast<const uint8_t*>(data.data());
    for (size_t split = 0; split <= data.size(); ++split) {
        Azure::Storage::Crc64Hash hash;
        hash.Append(bytes, split);
        auto result = hash.Final(bytes + split, data.size() - split);
        if (Azure::Core::Convert::Base64Encode(result) != "DtjZpL9/o8c=") return 1;
    }
    Azure::Storage::Crc64Hash empty;
    if (Azure::Core::Convert::Base64Encode(empty.Final()) != "AAAAAAAAAAA=") return 2;
    std::cout << "Installed Azure Storage CRC64 known-answer and streaming checks passed\n";
}
