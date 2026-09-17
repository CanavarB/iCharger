cmake_minimum_required(VERSION 3.14)
project(iCharger LANGUAGES CXX)

# 2. iCharger kütüphanesini tanımlar
add_library(iCharger STATIC
    iCharger.cpp
)

# 3. Kendi başlık (header) dosyalarının bulunduğu kök dizini dışarıya ve içeriye sunar
target_include_directories(iCharger PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 4. IUSBTransport interface kütüphanesini bağlar.
# PUBLIC seçildiği için iCharger'ı kullanan üst projeler (örn: Qt/Linux/Embedded app)
# IUSBTransport.hpp başlığına da doğrudan erişebilir.
target_link_libraries(iCharger PUBLIC IUSBTransport)
