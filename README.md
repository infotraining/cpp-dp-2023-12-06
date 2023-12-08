# Szkolenie - Wzorce projektowe w C++ #

## Ankieta

* https://forms.gle/rmkfU21cauWfYBvs5

## Dokumentacja + slajdy

* https://infotraining.bitbucket.io/cpp-dp

## Video

* https://infotrainingszkolenia-my.sharepoint.com/:v:/g/personal/krystian_piekos_infotraining_pl/Eaonrkxo6nBKnBcnVDi_zKkBDQUHgqKG7a9YFV96KZdHxw?e=KpCEjM&nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJTdHJlYW1XZWJBcHAiLCJyZWZlcnJhbFZpZXciOiJTaGFyZURpYWxvZy1MaW5rIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXcifX0%3D

* https://infotrainingszkolenia-my.sharepoint.com/:v:/g/personal/krystian_piekos_infotraining_pl/EYOBvrDDNbZPiT_1EfCfy1EBPk1m_x7B9JEzYDZhbH0m4g?e=FZohFw&nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJTdHJlYW1XZWJBcHAiLCJyZWZlcnJhbFZpZXciOiJTaGFyZURpYWxvZy1MaW5rIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXcifX0%3D

* https://infotrainingszkolenia-my.sharepoint.com/:v:/g/personal/krystian_piekos_infotraining_pl/ESmWxh5HwPRKh-ulbHdB7oMB4U1ET-XBcuq8DBLkNDFr-g?e=oWkWsZ&nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJTdHJlYW1XZWJBcHAiLCJyZWZlcnJhbFZpZXciOiJTaGFyZURpYWxvZy1MaW5rIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXcifX0%3D

## Konfiguracja środowiska

Proszę wybrać jedną z poniższych opcji:

### Lokalna

Przed szkoleniem należy zainstalować:

#### Kompilator C++ wspierający C++20 - do wyboru:
  * Visual Studio 2022
    * przy instalacji należy zaznaczyć opcje:
      * Desktop development with C++
      * C++ CMake tools for Windows
      * vcpkg package manager

  * GCC - Linux lub WSL
    * gcc (wersja >= 12)
    * [CMake > 3.25](https://cmake.org/)
      * proszę sprawdzić wersję w linii poleceń        
  
        ```
        cmake --version
        ```
    * vcpkg
      * instalacja - https://vcpkg.io/en/getting-started
      * dodać zmienną środowiskową VCPKG_ROOT
        * w pliku `.bashrc` należy dodać wpis

          ```
          export VCPKG_ROOT=[path to vcpkg root directory e.g. /user_name/home/vcpkg]
          ```
    * IDE: Visual Studio Code
      * [Visual Studio Code](https://code.visualstudio.com/)
      * zainstalować wtyczki
        * C/C++ Extension Pack
        * Live Share

### Docker + Visual Studio Code

Jeśli uczestnicy szkolenia korzystają w pracy z Docker'a, to należy zainstalować:

#### Docker Desktop (Windows)

* https://www.docker.com/products/docker-desktop/

#### Visual Studio Code

* [Visual Studio Code](https://code.visualstudio.com/)
* Zainstalować wtyczki
  * Live Share
  * Dev Containers ([wymagania](https://code.visualstudio.com/docs/devcontainers/containers#_system-requirements))
    * po instalacji wtyczki - należy otworzyć w VS Code folder zawierający sklonowane repozytorium i
      z palety poleceń (Ctrl+Shift+P) wybrać opcję **Dev Containers: Rebuild and Reopen in Container**