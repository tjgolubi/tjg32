/// @see https://reveng.sourceforge.io/crc-catalogue/all.htm

#pragma once

#include "Integer.h"
#include "meta.h"

namespace tjg {

constexpr int CrcDefaultSlices = 0;

struct Crc3Gsm {
  static constexpr const char* Name = "CRC-3/GSM";
  static constexpr std::size_t Bits = 3;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x3;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0;
  static constexpr CrcType XorOut = 0x7;
  static constexpr CrcType Check = 0x4;
  static constexpr CrcType Residue = 0x2;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc3Gsm

struct Crc3Rohc {
  static constexpr const char* Name = "CRC-3/ROHC";
  static constexpr std::size_t Bits = 3;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x3;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x7;
  static constexpr CrcType XorOut = 0x0;
  static constexpr CrcType Check = 0x6;
  static constexpr CrcType Residue = 0x0;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc3Rohc

struct Crc4G704 {
  static constexpr const char* Name = "CRC-4/G-704";
  static constexpr std::size_t Bits = 4;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x3;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x0;
  static constexpr CrcType XorOut = 0x0;
  static constexpr CrcType Check = 0x7;
  static constexpr CrcType Residue = 0x0;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc4G704

struct Crc4Interlaken {
  static constexpr const char* Name = "CRC-4/INTERLAKEN";
  static constexpr std::size_t Bits = 4;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x3;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xf;
  static constexpr CrcType XorOut = 0xf;
  static constexpr CrcType Check = 0xb;
  static constexpr CrcType Residue = 0x2;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc4Interlaken

struct Crc5EpcC1g2 {
  static constexpr const char* Name = "CRC-5/EPC-C1G2";
  static constexpr std::size_t Bits = 5;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x09;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x09;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x00;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc5EpcC1g2

struct Crc5G704 {
  static constexpr const char* Name = "CRC-5/G-704";
  static constexpr std::size_t Bits = 5;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x15;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x07;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc5G704

struct Crc5Usb {
  static constexpr const char* Name = "CRC-5/USB";
  static constexpr std::size_t Bits = 5;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x05;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x1f;
  static constexpr CrcType XorOut = 0x1f;
  static constexpr CrcType Check = 0x19;
  static constexpr CrcType Residue = 0x06;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc5Usb

struct Crc6Cdma2000A {
  static constexpr const char* Name = "CRC-6/CDMA2000-A";
  static constexpr std::size_t Bits = 6;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x27;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x3f;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x0d;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc6Cdma2000A

struct Crc6Cdma2000B {
  static constexpr const char* Name = "CRC-6/CDMA2000-B";
  static constexpr std::size_t Bits = 6;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x07;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x3f;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x3b;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc6Cdma2000B

struct Crc6Darc {
  static constexpr const char* Name = "CRC-6/DARC";
  static constexpr std::size_t Bits = 6;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x19;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x26;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc6Darc

struct Crc6G704 {
  static constexpr const char* Name = "CRC-6/G-704";
  static constexpr std::size_t Bits = 6;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x03;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x06;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc6G704

struct Crc6Gsm {
  static constexpr const char* Name = "CRC-6/GSM";
  static constexpr std::size_t Bits = 6;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x2f;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x3f;
  static constexpr CrcType Check = 0x13;
  static constexpr CrcType Residue = 0x3a;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc6Gsm

struct Crc7Mmc {
  static constexpr const char* Name = "CRC-7/MMC";
  static constexpr std::size_t Bits = 7;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x09;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x75;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc7Mmc

struct Crc7Rohc {
  static constexpr const char* Name = "CRC-7/ROHC";
  static constexpr std::size_t Bits = 7;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x4f;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x7f;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x53;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc7Rohc

struct Crc7Umts {
  static constexpr const char* Name = "CRC-7/UMTS";
  static constexpr std::size_t Bits = 7;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x45;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x61;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc7Umts

struct Crc8Autosar {
  static constexpr const char* Name = "CRC-8/AUTOSAR";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x2f;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xff;
  static constexpr CrcType XorOut = 0xff;
  static constexpr CrcType Check = 0xdf;
  static constexpr CrcType Residue = 0x42;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8Autosar

struct Crc8Bluetooth {
  static constexpr const char* Name = "CRC-8/BLUETOOTH";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0xa7;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x26;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8Bluetooth

struct Crc8Cdma2000 {
  static constexpr const char* Name = "CRC-8/CDMA2000";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x9b;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xff;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0xda;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8Cdma2000

struct Crc8Darc {
  static constexpr const char* Name = "CRC-8/DARC";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x39;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x15;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8Darc

struct Crc8DvbS2 {
  static constexpr const char* Name = "CRC-8/DVB-S2";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0xd5;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0xbc;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8DvbS2

struct Crc8GsmA {
  static constexpr const char* Name = "CRC-8/GSM-A";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1d;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x37;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8GsmA

struct Crc8GsmB {
  static constexpr const char* Name = "CRC-8/GSM-B";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x49;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0xff;
  static constexpr CrcType Check = 0x94;
  static constexpr CrcType Residue = 0x53;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8GsmB

struct Crc8Hitag {
  static constexpr const char* Name = "CRC-8/HITAG";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1d;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xff;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0xb4;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8Hitag

struct Crc8I4321 {
  static constexpr const char* Name = "CRC-8/I-432-1";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x07;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x55;
  static constexpr CrcType Check = 0xa1;
  static constexpr CrcType Residue = 0xac;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8I4321

struct Crc8ICode {
  static constexpr const char* Name = "CRC-8/I-CODE";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1d;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xfd;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x7e;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8ICode

struct Crc8Lte {
  static constexpr const char* Name = "CRC-8/LTE";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x9b;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0xea;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8Lte

struct Crc8MaximDow {
  static constexpr const char* Name = "CRC-8/MAXIM-DOW";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x31;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0xa1;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8MaximDow

struct Crc8MifareMad {
  static constexpr const char* Name = "CRC-8/MIFARE-MAD";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1d;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xc7;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x99;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8MifareMad

struct Crc8Nrsc5 {
  static constexpr const char* Name = "CRC-8/NRSC-5";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x31;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xff;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0xf7;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8Nrsc5

struct Crc8Opensafety {
  static constexpr const char* Name = "CRC-8/OPENSAFETY";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x2f;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x3e;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8Opensafety

struct Crc8Rohc {
  static constexpr const char* Name = "CRC-8/ROHC";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x07;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xff;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0xd0;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8Rohc

struct Crc8SaeJ1850 {
  static constexpr const char* Name = "CRC-8/SAE-J1850";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1d;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xff;
  static constexpr CrcType XorOut = 0xff;
  static constexpr CrcType Check = 0x4b;
  static constexpr CrcType Residue = 0xc4;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8SaeJ1850

struct Crc8Smbus {
  static constexpr const char* Name = "CRC-8/SMBUS";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x07;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0xf4;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8Smbus

struct Crc8Tech3250 {
  static constexpr const char* Name = "CRC-8/TECH-3250";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1d;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xff;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x97;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8Tech3250

struct Crc8Wcdma {
  static constexpr const char* Name = "CRC-8/WCDMA";
  static constexpr std::size_t Bits = 8;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x9b;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x00;
  static constexpr CrcType XorOut = 0x00;
  static constexpr CrcType Check = 0x25;
  static constexpr CrcType Residue = 0x00;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc8Wcdma

struct Crc10Atm {
  static constexpr const char* Name = "CRC-10/ATM";
  static constexpr std::size_t Bits = 10;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x233;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x000;
  static constexpr CrcType XorOut = 0x000;
  static constexpr CrcType Check = 0x199;
  static constexpr CrcType Residue = 0x000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc10Atm

struct Crc10Cdma2000 {
  static constexpr const char* Name = "CRC-10/CDMA2000";
  static constexpr std::size_t Bits = 10;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x3d9;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x3ff;
  static constexpr CrcType XorOut = 0x000;
  static constexpr CrcType Check = 0x233;
  static constexpr CrcType Residue = 0x000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc10Cdma2000

struct Crc10Gsm {
  static constexpr const char* Name = "CRC-10/GSM";
  static constexpr std::size_t Bits = 10;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x175;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x000;
  static constexpr CrcType XorOut = 0x3ff;
  static constexpr CrcType Check = 0x12a;
  static constexpr CrcType Residue = 0x0c6;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc10Gsm

struct Crc11Flexray {
  static constexpr const char* Name = "CRC-11/FLEXRAY";
  static constexpr std::size_t Bits = 11;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x385;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x01a;
  static constexpr CrcType XorOut = 0x000;
  static constexpr CrcType Check = 0x5a3;
  static constexpr CrcType Residue = 0x000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc11Flexray

struct Crc11Umts {
  static constexpr const char* Name = "CRC-11/UMTS";
  static constexpr std::size_t Bits = 11;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x307;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x000;
  static constexpr CrcType XorOut = 0x000;
  static constexpr CrcType Check = 0x061;
  static constexpr CrcType Residue = 0x000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc11Umts

struct Crc12Cdma2000 {
  static constexpr const char* Name = "CRC-12/CDMA2000";
  static constexpr std::size_t Bits = 12;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0xf13;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xfff;
  static constexpr CrcType XorOut = 0x000;
  static constexpr CrcType Check = 0xd4d;
  static constexpr CrcType Residue = 0x000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc12Cdma2000

struct Crc12Dect {
  static constexpr const char* Name = "CRC-12/DECT";
  static constexpr std::size_t Bits = 12;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x80f;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x000;
  static constexpr CrcType XorOut = 0x000;
  static constexpr CrcType Check = 0xf5b;
  static constexpr CrcType Residue = 0x000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc12Dect

struct Crc12Gsm {
  static constexpr const char* Name = "CRC-12/GSM";
  static constexpr std::size_t Bits = 12;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0xd31;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x000;
  static constexpr CrcType XorOut = 0xfff;
  static constexpr CrcType Check = 0xb34;
  static constexpr CrcType Residue = 0x178;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc12Gsm

struct Crc12Umts {
  static constexpr const char* Name = "CRC-12/UMTS";
  static constexpr std::size_t Bits = 12;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x80f;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x000;
  static constexpr CrcType XorOut = 0x000;
  static constexpr CrcType Check = 0xdaf;
  static constexpr CrcType Residue = 0x000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc12Umts

struct Crc13Bbc {
  static constexpr const char* Name = "CRC-13/BBC";
  static constexpr std::size_t Bits = 13;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1cf5;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x04fa;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc13Bbc

struct Crc14Darc {
  static constexpr const char* Name = "CRC-14/DARC";
  static constexpr std::size_t Bits = 14;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x0805;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x082d;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc14Darc

struct Crc14Gsm {
  static constexpr const char* Name = "CRC-14/GSM";
  static constexpr std::size_t Bits = 14;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x202d;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x3fff;
  static constexpr CrcType Check = 0x30ae;
  static constexpr CrcType Residue = 0x031e;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc14Gsm

struct Crc15Can {
  static constexpr const char* Name = "CRC-15/CAN";
  static constexpr std::size_t Bits = 15;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x4599;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x059e;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc15Can

struct Crc15Mpt1327 {
  static constexpr const char* Name = "CRC-15/MPT1327";
  static constexpr std::size_t Bits = 15;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x6815;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0001;
  static constexpr CrcType Check = 0x2566;
  static constexpr CrcType Residue = 0x6815;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc15Mpt1327

struct Crc16Arc {
  static constexpr const char* Name = "CRC-16/ARC";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x8005;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0xbb3d;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Arc

struct Crc16Cdma2000 {
  static constexpr const char* Name = "CRC-16/CDMA2000";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0xc867;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xffff;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x4c06;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Cdma2000

struct Crc16Cms {
  static constexpr const char* Name = "CRC-16/CMS";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x8005;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xffff;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0xaee7;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Cms

struct Crc16Dds110 {
  static constexpr const char* Name = "CRC-16/DDS-110";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x8005;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x800d;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x9ecf;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Dds110

struct Crc16DectR {
  static constexpr const char* Name = "CRC-16/DECT-R";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x0589;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0001;
  static constexpr CrcType Check = 0x007e;
  static constexpr CrcType Residue = 0x0589;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16DectR

struct Crc16DectX {
  static constexpr const char* Name = "CRC-16/DECT-X";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x0589;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x007f;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16DectX

struct Crc16Dnp {
  static constexpr const char* Name = "CRC-16/DNP";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x3d65;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0xffff;
  static constexpr CrcType Check = 0xea82;
  static constexpr CrcType Residue = 0x66c5;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Dnp

struct Crc16En13757 {
  static constexpr const char* Name = "CRC-16/EN-13757";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x3d65;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0xffff;
  static constexpr CrcType Check = 0xc2b7;
  static constexpr CrcType Residue = 0xa366;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16En13757

struct Crc16Genibus {
  static constexpr const char* Name = "CRC-16/GENIBUS";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1021;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xffff;
  static constexpr CrcType XorOut = 0xffff;
  static constexpr CrcType Check = 0xd64e;
  static constexpr CrcType Residue = 0x1d0f;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Genibus

struct Crc16Gsm {
  static constexpr const char* Name = "CRC-16/GSM";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1021;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0xffff;
  static constexpr CrcType Check = 0xce3c;
  static constexpr CrcType Residue = 0x1d0f;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Gsm

struct Crc16Ibm3740 {
  static constexpr const char* Name = "CRC-16/IBM-3740";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1021;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xffff;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x29b1;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Ibm3740

struct Crc16IbmSdlc {
  static constexpr const char* Name = "CRC-16/IBM-SDLC";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1021;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffff;
  static constexpr CrcType XorOut = 0xffff;
  static constexpr CrcType Check = 0x906e;
  static constexpr CrcType Residue = 0xf0b8;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16IbmSdlc

struct Crc16IsoIec144433A {
  static constexpr const char* Name = "CRC-16/ISO-IEC-14443-3-A";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1021;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xc6c6;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0xbf05;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16IsoIec144433A

struct Crc16Kermit {
  static constexpr const char* Name = "CRC-16/KERMIT";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1021;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x2189;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Kermit

struct Crc16Lj1200 {
  static constexpr const char* Name = "CRC-16/LJ1200";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x6f63;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0xbdf4;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Lj1200

struct Crc16M17 {
  static constexpr const char* Name = "CRC-16/M17";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x5935;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xffff;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x772b;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16M17

struct Crc16MaximDow {
  static constexpr const char* Name = "CRC-16/MAXIM-DOW";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x8005;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0xffff;
  static constexpr CrcType Check = 0x44c2;
  static constexpr CrcType Residue = 0xb001;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16MaximDow

struct Crc16Mcrf4xx {
  static constexpr const char* Name = "CRC-16/MCRF4XX";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1021;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffff;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x6f91;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Mcrf4xx

struct Crc16Modbus {
  static constexpr const char* Name = "CRC-16/MODBUS";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x8005;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffff;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x4b37;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Modbus

struct Crc16Nrsc5 {
  static constexpr const char* Name = "CRC-16/NRSC-5";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x080b;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffff;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0xa066;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Nrsc5

struct Crc16OpensafetyA {
  static constexpr const char* Name = "CRC-16/OPENSAFETY-A";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x5935;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x5d38;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16OpensafetyA

struct Crc16OpensafetyB {
  static constexpr const char* Name = "CRC-16/OPENSAFETY-B";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x755b;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x20fe;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16OpensafetyB

struct Crc16Profibus {
  static constexpr const char* Name = "CRC-16/PROFIBUS";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1dcf;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xffff;
  static constexpr CrcType XorOut = 0xffff;
  static constexpr CrcType Check = 0xa819;
  static constexpr CrcType Residue = 0xe394;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Profibus

struct Crc16Riello {
  static constexpr const char* Name = "CRC-16/RIELLO";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1021;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xb2aa;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x63d0;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Riello

struct Crc16SpiFujitsu {
  static constexpr const char* Name = "CRC-16/SPI-FUJITSU";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1021;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x1d0f;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0xe5cc;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16SpiFujitsu

struct Crc16T10Dif {
  static constexpr const char* Name = "CRC-16/T10-DIF";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x8bb7;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0xd0db;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16T10Dif

struct Crc16Teledisk {
  static constexpr const char* Name = "CRC-16/TELEDISK";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0xa097;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x0fb3;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Teledisk

struct Crc16Tms37157 {
  static constexpr const char* Name = "CRC-16/TMS37157";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1021;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x89ec;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x26b1;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Tms37157

struct Crc16Umts {
  static constexpr const char* Name = "CRC-16/UMTS";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x8005;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0xfee8;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Umts

struct Crc16Usb {
  static constexpr const char* Name = "CRC-16/USB";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x8005;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffff;
  static constexpr CrcType XorOut = 0xffff;
  static constexpr CrcType Check = 0xb4c8;
  static constexpr CrcType Residue = 0xb001;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Usb

struct Crc16Xmodem {
  static constexpr const char* Name = "CRC-16/XMODEM";
  static constexpr std::size_t Bits = 16;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1021;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000;
  static constexpr CrcType XorOut = 0x0000;
  static constexpr CrcType Check = 0x31c3;
  static constexpr CrcType Residue = 0x0000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc16Xmodem

struct Crc17CanFd {
  static constexpr const char* Name = "CRC-17/CAN-FD";
  static constexpr std::size_t Bits = 17;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1685b;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00000;
  static constexpr CrcType XorOut = 0x00000;
  static constexpr CrcType Check = 0x04f03;
  static constexpr CrcType Residue = 0x00000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc17CanFd

struct Crc21CanFd {
  static constexpr const char* Name = "CRC-21/CAN-FD";
  static constexpr std::size_t Bits = 21;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x102899;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x000000;
  static constexpr CrcType XorOut = 0x000000;
  static constexpr CrcType Check = 0x0ed841;
  static constexpr CrcType Residue = 0x000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc21CanFd

struct Crc24Ble {
  static constexpr const char* Name = "CRC-24/BLE";
  static constexpr std::size_t Bits = 24;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x00065b;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x555555;
  static constexpr CrcType XorOut = 0x000000;
  static constexpr CrcType Check = 0xc25a56;
  static constexpr CrcType Residue = 0x000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc24Ble

struct Crc24FlexrayA {
  static constexpr const char* Name = "CRC-24/FLEXRAY-A";
  static constexpr std::size_t Bits = 24;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x5d6dcb;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xfedcba;
  static constexpr CrcType XorOut = 0x000000;
  static constexpr CrcType Check = 0x7979bd;
  static constexpr CrcType Residue = 0x000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc24FlexrayA

struct Crc24FlexrayB {
  static constexpr const char* Name = "CRC-24/FLEXRAY-B";
  static constexpr std::size_t Bits = 24;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x5d6dcb;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xabcdef;
  static constexpr CrcType XorOut = 0x000000;
  static constexpr CrcType Check = 0x1f23b8;
  static constexpr CrcType Residue = 0x000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc24FlexrayB

struct Crc24Interlaken {
  static constexpr const char* Name = "CRC-24/INTERLAKEN";
  static constexpr std::size_t Bits = 24;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x328b63;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xffffff;
  static constexpr CrcType XorOut = 0xffffff;
  static constexpr CrcType Check = 0xb4f3e6;
  static constexpr CrcType Residue = 0x144e63;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc24Interlaken

struct Crc24LteA {
  static constexpr const char* Name = "CRC-24/LTE-A";
  static constexpr std::size_t Bits = 24;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x864cfb;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x000000;
  static constexpr CrcType XorOut = 0x000000;
  static constexpr CrcType Check = 0xcde703;
  static constexpr CrcType Residue = 0x000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc24LteA

struct Crc24LteB {
  static constexpr const char* Name = "CRC-24/LTE-B";
  static constexpr std::size_t Bits = 24;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x800063;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x000000;
  static constexpr CrcType XorOut = 0x000000;
  static constexpr CrcType Check = 0x23ef52;
  static constexpr CrcType Residue = 0x000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc24LteB

struct Crc24Openpgp {
  static constexpr const char* Name = "CRC-24/OPENPGP";
  static constexpr std::size_t Bits = 24;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x864cfb;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xb704ce;
  static constexpr CrcType XorOut = 0x000000;
  static constexpr CrcType Check = 0x21cf02;
  static constexpr CrcType Residue = 0x000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc24Openpgp

struct Crc24Os9 {
  static constexpr const char* Name = "CRC-24/OS-9";
  static constexpr std::size_t Bits = 24;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x800063;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xffffff;
  static constexpr CrcType XorOut = 0xffffff;
  static constexpr CrcType Check = 0x200fa5;
  static constexpr CrcType Residue = 0x800fe3;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc24Os9

struct Crc30Cdma {
  static constexpr const char* Name = "CRC-30/CDMA";
  static constexpr std::size_t Bits = 30;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x2030b9c7;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x3fffffff;
  static constexpr CrcType XorOut = 0x3fffffff;
  static constexpr CrcType Check = 0x04c34abf;
  static constexpr CrcType Residue = 0x34efa55a;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc30Cdma

struct Crc31Philips {
  static constexpr const char* Name = "CRC-31/PHILIPS";
  static constexpr std::size_t Bits = 31;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x04c11db7;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x7fffffff;
  static constexpr CrcType XorOut = 0x7fffffff;
  static constexpr CrcType Check = 0x0ce9e46c;
  static constexpr CrcType Residue = 0x4eaf26f1;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc31Philips

struct Crc32Aixm {
  static constexpr const char* Name = "CRC-32/AIXM";
  static constexpr std::size_t Bits = 32;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x814141ab;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00000000;
  static constexpr CrcType XorOut = 0x00000000;
  static constexpr CrcType Check = 0x3010bf7f;
  static constexpr CrcType Residue = 0x00000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc32Aixm

struct Crc32Autosar {
  static constexpr const char* Name = "CRC-32/AUTOSAR";
  static constexpr std::size_t Bits = 32;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0xf4acfb13;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffffffff;
  static constexpr CrcType XorOut = 0xffffffff;
  static constexpr CrcType Check = 0x1697d06a;
  static constexpr CrcType Residue = 0x904cddbf;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc32Autosar

struct Crc32Base91D {
  static constexpr const char* Name = "CRC-32/BASE91-D";
  static constexpr std::size_t Bits = 32;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0xa833982b;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffffffff;
  static constexpr CrcType XorOut = 0xffffffff;
  static constexpr CrcType Check = 0x87315576;
  static constexpr CrcType Residue = 0x45270551;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc32Base91D

struct Crc32Bzip2 {
  static constexpr const char* Name = "CRC-32/BZIP2";
  static constexpr std::size_t Bits = 32;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x04c11db7;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xffffffff;
  static constexpr CrcType XorOut = 0xffffffff;
  static constexpr CrcType Check = 0xfc891918;
  static constexpr CrcType Residue = 0xc704dd7b;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc32Bzip2

struct Crc32CdRomEdc {
  static constexpr const char* Name = "CRC-32/CD-ROM-EDC";
  static constexpr std::size_t Bits = 32;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x8001801b;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x00000000;
  static constexpr CrcType XorOut = 0x00000000;
  static constexpr CrcType Check = 0x6ec2edc4;
  static constexpr CrcType Residue = 0x00000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc32CdRomEdc

struct Crc32Cksum {
  static constexpr const char* Name = "CRC-32/CKSUM";
  static constexpr std::size_t Bits = 32;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x04c11db7;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00000000;
  static constexpr CrcType XorOut = 0xffffffff;
  static constexpr CrcType Check = 0x765e7680;
  static constexpr CrcType Residue = 0xc704dd7b;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc32Cksum

struct Crc32Iscsi {
  static constexpr const char* Name = "CRC-32/ISCSI";
  static constexpr std::size_t Bits = 32;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x1edc6f41;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffffffff;
  static constexpr CrcType XorOut = 0xffffffff;
  static constexpr CrcType Check = 0xe3069283;
  static constexpr CrcType Residue = 0xb798b438;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc32Iscsi

struct Crc32IsoHdlc {
  static constexpr const char* Name = "CRC-32/ISO-HDLC";
  static constexpr std::size_t Bits = 32;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x04c11db7;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffffffff;
  static constexpr CrcType XorOut = 0xffffffff;
  static constexpr CrcType Check = 0xcbf43926;
  static constexpr CrcType Residue = 0xdebb20e3;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc32IsoHdlc

struct Crc32Jamcrc {
  static constexpr const char* Name = "CRC-32/JAMCRC";
  static constexpr std::size_t Bits = 32;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x04c11db7;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffffffff;
  static constexpr CrcType XorOut = 0x00000000;
  static constexpr CrcType Check = 0x340bc6d9;
  static constexpr CrcType Residue = 0x00000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc32Jamcrc

struct Crc32Mef {
  static constexpr const char* Name = "CRC-32/MEF";
  static constexpr std::size_t Bits = 32;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x741b8cd7;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffffffff;
  static constexpr CrcType XorOut = 0x00000000;
  static constexpr CrcType Check = 0xd2c22f51;
  static constexpr CrcType Residue = 0x00000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc32Mef

struct Crc32Mpeg2 {
  static constexpr const char* Name = "CRC-32/MPEG-2";
  static constexpr std::size_t Bits = 32;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x04c11db7;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xffffffff;
  static constexpr CrcType XorOut = 0x00000000;
  static constexpr CrcType Check = 0x0376e6e7;
  static constexpr CrcType Residue = 0x00000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc32Mpeg2

struct Crc32Xfer {
  static constexpr const char* Name = "CRC-32/XFER";
  static constexpr std::size_t Bits = 32;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x000000af;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x00000000;
  static constexpr CrcType XorOut = 0x00000000;
  static constexpr CrcType Check = 0xbd0be338;
  static constexpr CrcType Residue = 0x00000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc32Xfer

struct Crc40Gsm {
  static constexpr const char* Name = "CRC-40/GSM";
  static constexpr std::size_t Bits = 40;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x0004820009;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000000000;
  static constexpr CrcType XorOut = 0xffffffffff;
  static constexpr CrcType Check = 0xd4164fc646;
  static constexpr CrcType Residue = 0xc4ff8071ff;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc40Gsm

struct Crc64Ecma182 {
  static constexpr const char* Name = "CRC-64/ECMA-182";
  static constexpr std::size_t Bits = 64;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x42f0e1eba9ea3693;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0x0000000000000000;
  static constexpr CrcType XorOut = 0x0000000000000000;
  static constexpr CrcType Check = 0x6c40df5f0b497347;
  static constexpr CrcType Residue = 0x0000000000000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc64Ecma182

struct Crc64GoIso {
  static constexpr const char* Name = "CRC-64/GO-ISO";
  static constexpr std::size_t Bits = 64;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x000000000000001b;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffffffffffffffff;
  static constexpr CrcType XorOut = 0xffffffffffffffff;
  static constexpr CrcType Check = 0xb90956c775a41001;
  static constexpr CrcType Residue = 0x5300000000000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc64GoIso

struct Crc64Ms {
  static constexpr const char* Name = "CRC-64/MS";
  static constexpr std::size_t Bits = 64;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x259c84cba6426349;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffffffffffffffff;
  static constexpr CrcType XorOut = 0x0000000000000000;
  static constexpr CrcType Check = 0x75d4b74f024eceea;
  static constexpr CrcType Residue = 0x0000000000000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc64Ms

struct Crc64Nvme {
  static constexpr const char* Name = "CRC-64/NVME";
  static constexpr std::size_t Bits = 64;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0xad93d23594c93659;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffffffffffffffff;
  static constexpr CrcType XorOut = 0xffffffffffffffff;
  static constexpr CrcType Check = 0xae8b14860a799888;
  static constexpr CrcType Residue = 0xf310303b2b6f6e42;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc64Nvme

struct Crc64Redis {
  static constexpr const char* Name = "CRC-64/REDIS";
  static constexpr std::size_t Bits = 64;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0xad93d23594c935a9;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x0000000000000000;
  static constexpr CrcType XorOut = 0x0000000000000000;
  static constexpr CrcType Check = 0xe9c6d914c4b8d9ca;
  static constexpr CrcType Residue = 0x0000000000000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc64Redis

struct Crc64We {
  static constexpr const char* Name = "CRC-64/WE";
  static constexpr std::size_t Bits = 64;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x42f0e1eba9ea3693;
  static constexpr bool ReflectIn = false;
  static constexpr bool ReflectOut = false;
  static constexpr CrcType Init = 0xffffffffffffffff;
  static constexpr CrcType XorOut = 0xffffffffffffffff;
  static constexpr CrcType Check = 0x62ec59e3f1a4f00a;
  static constexpr CrcType Residue = 0xfcacbebd5931a992;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc64We

struct Crc64Xz {
  static constexpr const char* Name = "CRC-64/XZ";
  static constexpr std::size_t Bits = 64;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x42f0e1eba9ea3693;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0xffffffffffffffff;
  static constexpr CrcType XorOut = 0xffffffffffffffff;
  static constexpr CrcType Check = 0x995dc9bbdf1939fa;
  static constexpr CrcType Residue = 0x49958c9abd7d353f;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc64Xz

#if 0
struct Crc82Darc {
  static constexpr const char* Name = "CRC-82/DARC";
  static constexpr std::size_t Bits = 82;
  using CrcType = uint_t<Bits>::least;
  static constexpr CrcType Poly = 0x0308c0111011401440411;
  static constexpr bool ReflectIn = true;
  static constexpr bool ReflectOut = true;
  static constexpr CrcType Init = 0x000000000000000000000;
  static constexpr CrcType XorOut = 0x000000000000000000000;
  static constexpr CrcType Check = 0x09ea83f625023801fd612;
  static constexpr CrcType Residue = 0x000000000000000000000;
  static constexpr int Slices = CrcDefaultSlices;
}; // Crc82Darc
#endif

using KnownCrcs = meta::TypeList<
  Crc3Gsm,
  Crc3Rohc,
  Crc4G704,
  Crc4Interlaken,
  Crc5EpcC1g2,
  Crc5G704,
  Crc5Usb,
  Crc6Cdma2000A,
  Crc6Cdma2000B,
  Crc6Darc,
  Crc6G704,
  Crc6Gsm,
  Crc7Mmc,
  Crc7Rohc,
  Crc7Umts,
  Crc8Autosar,
  Crc8Bluetooth,
  Crc8Cdma2000,
  Crc8Darc,
  Crc8DvbS2,
  Crc8GsmA,
  Crc8GsmB,
  Crc8Hitag,
  Crc8I4321,
  Crc8ICode,
  Crc8Lte,
  Crc8MaximDow,
  Crc8MifareMad,
  Crc8Nrsc5,
  Crc8Opensafety,
  Crc8Rohc,
  Crc8SaeJ1850,
  Crc8Smbus,
  Crc8Tech3250,
  Crc8Wcdma,
  Crc10Atm,
  Crc10Cdma2000,
  Crc10Gsm,
  Crc11Flexray,
  Crc11Umts,
  Crc12Cdma2000,
  Crc12Dect,
  Crc12Gsm,
  Crc12Umts,
  Crc13Bbc,
  Crc14Darc,
  Crc14Gsm,
  Crc15Can,
  Crc15Mpt1327,
  Crc16Arc,
  Crc16Cdma2000,
  Crc16Cms,
  Crc16Dds110,
  Crc16DectR,
  Crc16DectX,
  Crc16Dnp,
  Crc16En13757,
  Crc16Genibus,
  Crc16Gsm,
  Crc16Ibm3740,
  Crc16IbmSdlc,
  Crc16IsoIec144433A,
  Crc16Kermit,
  Crc16Lj1200,
  Crc16M17,
  Crc16MaximDow,
  Crc16Mcrf4xx,
  Crc16Modbus,
  Crc16Nrsc5,
  Crc16OpensafetyA,
  Crc16OpensafetyB,
  Crc16Profibus,
  Crc16Riello,
  Crc16SpiFujitsu,
  Crc16T10Dif,
  Crc16Teledisk,
  Crc16Tms37157,
  Crc16Umts,
  Crc16Usb,
  Crc16Xmodem,
  Crc17CanFd,
  Crc21CanFd,
  Crc24Ble,
  Crc24FlexrayA,
  Crc24FlexrayB,
  Crc24Interlaken,
  Crc24LteA,
  Crc24LteB,
  Crc24Openpgp,
  Crc24Os9,
  Crc30Cdma,
  Crc31Philips,
  Crc32Aixm,
  Crc32Autosar,
  Crc32Base91D,
  Crc32Bzip2,
  Crc32CdRomEdc,
  Crc32Cksum,
  Crc32Iscsi,
  Crc32IsoHdlc,
  Crc32Jamcrc,
  Crc32Mef,
  Crc32Mpeg2,
  Crc32Xfer,
  Crc40Gsm,
  Crc64Ecma182,
  Crc64GoIso,
  Crc64Ms,
  Crc64Nvme,
  Crc64Redis,
  Crc64We,
  Crc64Xz
>; // KnownCrcs

template<class T>
struct IsAbnormal
  : std::bool_constant<T::Bits !=  8 && T::Bits != 16
                    && T::Bits != 32 && T::Bits != 64> { };

using KnownAbnormalCrcs = meta::FilterT<IsAbnormal, KnownCrcs>;

template<std::size_t N>
struct IsBitsEqual {
  template<class T>
  using apply = std::bool_constant<T::Bits == N>;
};

template<std::size_t N>
using KnownNBitCrcs =
                      meta::FilterT<IsBitsEqual<N>::template apply, KnownCrcs>;
using Known8BitCrs   = KnownNBitCrcs< 8>;
using Known16BitCrcs = KnownNBitCrcs<16>;
using Known32BitCrcs = KnownNBitCrcs<32>;
using Known64BitCrcs = KnownNBitCrcs<64>;

} // tjg
