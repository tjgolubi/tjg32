/// @see https://reveng.sourceforge.io/crc-catalogue/all.htm

#include "CrcEngine.h"

#include "meta.h"

namespace tjg {

struct Crc3Gsm : public CrcEngine<3, 0x3, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x4;
  static constexpr const char* Name = "CRC-3/GSM";
  Crc3Gsm() : CrcEngine{0x0, 0x7} { }
};

struct Crc3Rohc : public CrcEngine<3, 0x3, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x6;
  static constexpr const char* Name = "CRC-3/ROHC";
  Crc3Rohc() : CrcEngine{0x7, 0x0} { }
};

struct Crc4G704 : public CrcEngine<4, 0x3, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x7;
  static constexpr const char* Name = "CRC-4/G-704";
  Crc4G704() : CrcEngine{0x0, 0x0} { }
};

struct Crc4Interlaken : public CrcEngine<4, 0x3, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xb;
  static constexpr const char* Name = "CRC-4/INTERLAKEN";
  Crc4Interlaken() : CrcEngine{0xf, 0xf} { }
};

struct Crc5EpcC1g2 : public CrcEngine<5, 0x09, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x00;
  static constexpr const char* Name = "CRC-5/EPC-C1G2";
  Crc5EpcC1g2() : CrcEngine{0x09, 0x00} { }
};

struct Crc5G704 : public CrcEngine<5, 0x15, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x07;
  static constexpr const char* Name = "CRC-5/G-704";
  Crc5G704() : CrcEngine{0x00, 0x00} { }
};

struct Crc5Usb : public CrcEngine<5, 0x05, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x19;
  static constexpr const char* Name = "CRC-5/USB";
  Crc5Usb() : CrcEngine{0x1f, 0x1f} { }
};

struct Crc6Cdma2000A : public CrcEngine<6, 0x27, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x0d;
  static constexpr const char* Name = "CRC-6/CDMA2000-A";
  Crc6Cdma2000A() : CrcEngine{0x3f, 0x00} { }
};

struct Crc6Cdma2000B : public CrcEngine<6, 0x07, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x3b;
  static constexpr const char* Name = "CRC-6/CDMA2000-B";
  Crc6Cdma2000B() : CrcEngine{0x3f, 0x00} { }
};

struct Crc6Darc : public CrcEngine<6, 0x19, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x26;
  static constexpr const char* Name = "CRC-6/DARC";
  Crc6Darc() : CrcEngine{0x00, 0x00} { }
};

struct Crc6G704 : public CrcEngine<6, 0x03, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x06;
  static constexpr const char* Name = "CRC-6/G-704";
  Crc6G704() : CrcEngine{0x00, 0x00} { }
};

struct Crc6Gsm : public CrcEngine<6, 0x2f, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x13;
  static constexpr const char* Name = "CRC-6/GSM";
  Crc6Gsm() : CrcEngine{0x00, 0x3f} { }
};

struct Crc7Mmc : public CrcEngine<7, 0x09, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x75;
  static constexpr const char* Name = "CRC-7/MMC";
  Crc7Mmc() : CrcEngine{0x00, 0x00} { }
};

struct Crc7Rohc : public CrcEngine<7, 0x4f, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x53;
  static constexpr const char* Name = "CRC-7/ROHC";
  Crc7Rohc() : CrcEngine{0x7f, 0x00} { }
};

struct Crc7Umts : public CrcEngine<7, 0x45, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x61;
  static constexpr const char* Name = "CRC-7/UMTS";
  Crc7Umts() : CrcEngine{0x00, 0x00} { }
};

struct Crc8Autosar : public CrcEngine<8, 0x2f, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xdf;
  static constexpr const char* Name = "CRC-8/AUTOSAR";
  Crc8Autosar() : CrcEngine{0xff, 0xff} { }
};

struct Crc8Bluetooth : public CrcEngine<8, 0xa7, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x26;
  static constexpr const char* Name = "CRC-8/BLUETOOTH";
  Crc8Bluetooth() : CrcEngine{0x00, 0x00} { }
};

struct Crc8Cdma2000 : public CrcEngine<8, 0x9b, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xda;
  static constexpr const char* Name = "CRC-8/CDMA2000";
  Crc8Cdma2000() : CrcEngine{0xff, 0x00} { }
};

struct Crc8Darc : public CrcEngine<8, 0x39, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x15;
  static constexpr const char* Name = "CRC-8/DARC";
  Crc8Darc() : CrcEngine{0x00, 0x00} { }
};

struct Crc8DvbS2 : public CrcEngine<8, 0xd5, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xbc;
  static constexpr const char* Name = "CRC-8/DVB-S2";
  Crc8DvbS2() : CrcEngine{0x00, 0x00} { }
};

struct Crc8GsmA : public CrcEngine<8, 0x1d, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x37;
  static constexpr const char* Name = "CRC-8/GSM-A";
  Crc8GsmA() : CrcEngine{0x00, 0x00} { }
};

struct Crc8GsmB : public CrcEngine<8, 0x49, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x94;
  static constexpr const char* Name = "CRC-8/GSM-B";
  Crc8GsmB() : CrcEngine{0x00, 0xff} { }
};

struct Crc8Hitag : public CrcEngine<8, 0x1d, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xb4;
  static constexpr const char* Name = "CRC-8/HITAG";
  Crc8Hitag() : CrcEngine{0xff, 0x00} { }
};

struct Crc8I4321 : public CrcEngine<8, 0x07, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xa1;
  static constexpr const char* Name = "CRC-8/I-432-1";
  Crc8I4321() : CrcEngine{0x00, 0x55} { }
};

struct Crc8ICode : public CrcEngine<8, 0x1d, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x7e;
  static constexpr const char* Name = "CRC-8/I-CODE";
  Crc8ICode() : CrcEngine{0xfd, 0x00} { }
};

struct Crc8Lte : public CrcEngine<8, 0x9b, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xea;
  static constexpr const char* Name = "CRC-8/LTE";
  Crc8Lte() : CrcEngine{0x00, 0x00} { }
};

struct Crc8MaximDow : public CrcEngine<8, 0x31, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xa1;
  static constexpr const char* Name = "CRC-8/MAXIM-DOW";
  Crc8MaximDow() : CrcEngine{0x00, 0x00} { }
};

struct Crc8MifareMad : public CrcEngine<8, 0x1d, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x99;
  static constexpr const char* Name = "CRC-8/MIFARE-MAD";
  Crc8MifareMad() : CrcEngine{0xc7, 0x00} { }
};

struct Crc8Nrsc5 : public CrcEngine<8, 0x31, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xf7;
  static constexpr const char* Name = "CRC-8/NRSC-5";
  Crc8Nrsc5() : CrcEngine{0xff, 0x00} { }
};

struct Crc8Opensafety : public CrcEngine<8, 0x2f, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x3e;
  static constexpr const char* Name = "CRC-8/OPENSAFETY";
  Crc8Opensafety() : CrcEngine{0x00, 0x00} { }
};

struct Crc8Rohc : public CrcEngine<8, 0x07, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xd0;
  static constexpr const char* Name = "CRC-8/ROHC";
  Crc8Rohc() : CrcEngine{0xff, 0x00} { }
};

struct Crc8SaeJ1850 : public CrcEngine<8, 0x1d, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x4b;
  static constexpr const char* Name = "CRC-8/SAE-J1850";
  Crc8SaeJ1850() : CrcEngine{0xff, 0xff} { }
};

struct Crc8Smbus : public CrcEngine<8, 0x07, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xf4;
  static constexpr const char* Name = "CRC-8/SMBUS";
  Crc8Smbus() : CrcEngine{0x00, 0x00} { }
};

struct Crc8Tech3250 : public CrcEngine<8, 0x1d, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x97;
  static constexpr const char* Name = "CRC-8/TECH-3250";
  Crc8Tech3250() : CrcEngine{0xff, 0x00} { }
};

struct Crc8Wcdma : public CrcEngine<8, 0x9b, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x25;
  static constexpr const char* Name = "CRC-8/WCDMA";
  Crc8Wcdma() : CrcEngine{0x00, 0x00} { }
};

struct Crc10Atm : public CrcEngine<10, 0x233, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x199;
  static constexpr const char* Name = "CRC-10/ATM";
  Crc10Atm() : CrcEngine{0x000, 0x000} { }
};

struct Crc10Cdma2000 : public CrcEngine<10, 0x3d9, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x233;
  static constexpr const char* Name = "CRC-10/CDMA2000";
  Crc10Cdma2000() : CrcEngine{0x3ff, 0x000} { }
};

struct Crc10Gsm : public CrcEngine<10, 0x175, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x12a;
  static constexpr const char* Name = "CRC-10/GSM";
  Crc10Gsm() : CrcEngine{0x000, 0x3ff} { }
};

struct Crc11Flexray : public CrcEngine<11, 0x385, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x5a3;
  static constexpr const char* Name = "CRC-11/FLEXRAY";
  Crc11Flexray() : CrcEngine{0x01a, 0x000} { }
};

struct Crc11Umts : public CrcEngine<11, 0x307, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x061;
  static constexpr const char* Name = "CRC-11/UMTS";
  Crc11Umts() : CrcEngine{0x000, 0x000} { }
};

struct Crc12Cdma2000 : public CrcEngine<12, 0xf13, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xd4d;
  static constexpr const char* Name = "CRC-12/CDMA2000";
  Crc12Cdma2000() : CrcEngine{0xfff, 0x000} { }
};

struct Crc12Dect : public CrcEngine<12, 0x80f, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xf5b;
  static constexpr const char* Name = "CRC-12/DECT";
  Crc12Dect() : CrcEngine{0x000, 0x000} { }
};

struct Crc12Gsm : public CrcEngine<12, 0xd31, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xb34;
  static constexpr const char* Name = "CRC-12/GSM";
  Crc12Gsm() : CrcEngine{0x000, 0xfff} { }
};

struct Crc12Umts : public CrcEngine<12, 0x80f, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xdaf;
  static constexpr const char* Name = "CRC-12/UMTS";
  Crc12Umts() : CrcEngine{0x000, 0x000} { }
  CrcType value() const { return Reflect(CrcEngine::value()) >> Shift; }
};

struct Crc13Bbc : public CrcEngine<13, 0x1cf5, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x04fa;
  static constexpr const char* Name = "CRC-13/BBC";
  Crc13Bbc() : CrcEngine{0x0000, 0x0000} { }
};

struct Crc14Darc : public CrcEngine<14, 0x0805, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x082d;
  static constexpr const char* Name = "CRC-14/DARC";
  Crc14Darc() : CrcEngine{0x0000, 0x0000} { }
};

struct Crc14Gsm : public CrcEngine<14, 0x202d, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x30ae;
  static constexpr const char* Name = "CRC-14/GSM";
  Crc14Gsm() : CrcEngine{0x0000, 0x3fff} { }
};

struct Crc15Can : public CrcEngine<15, 0x4599, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x059e;
  static constexpr const char* Name = "CRC-15/CAN";
  Crc15Can() : CrcEngine{0x0000, 0x0000} { }
};

struct Crc15Mpt1327 : public CrcEngine<15, 0x6815, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x2566;
  static constexpr const char* Name = "CRC-15/MPT1327";
  Crc15Mpt1327() : CrcEngine{0x0000, 0x0001} { }
};

struct Crc16Arc : public CrcEngine<16, 0x8005, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xbb3d;
  static constexpr const char* Name = "CRC-16/ARC";
  Crc16Arc() : CrcEngine{0x0000, 0x0000} { }
};

struct Crc16Cdma2000 : public CrcEngine<16, 0xc867, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x4c06;
  static constexpr const char* Name = "CRC-16/CDMA2000";
  Crc16Cdma2000() : CrcEngine{0xffff, 0x0000} { }
};

struct Crc16Cms : public CrcEngine<16, 0x8005, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xaee7;
  static constexpr const char* Name = "CRC-16/CMS";
  Crc16Cms() : CrcEngine{0xffff, 0x0000} { }
};

struct Crc16Dds110 : public CrcEngine<16, 0x8005, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x9ecf;
  static constexpr const char* Name = "CRC-16/DDS-110";
  Crc16Dds110() : CrcEngine{0x800d, 0x0000} { }
};

struct Crc16DectR : public CrcEngine<16, 0x0589, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x007e;
  static constexpr const char* Name = "CRC-16/DECT-R";
  Crc16DectR() : CrcEngine{0x0000, 0x0001} { }
};

struct Crc16DectX : public CrcEngine<16, 0x0589, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x007f;
  static constexpr const char* Name = "CRC-16/DECT-X";
  Crc16DectX() : CrcEngine{0x0000, 0x0000} { }
};

struct Crc16Dnp : public CrcEngine<16, 0x3d65, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xea82;
  static constexpr const char* Name = "CRC-16/DNP";
  Crc16Dnp() : CrcEngine{0x0000, 0xffff} { }
};

struct Crc16En13757 : public CrcEngine<16, 0x3d65, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xc2b7;
  static constexpr const char* Name = "CRC-16/EN-13757";
  Crc16En13757() : CrcEngine{0x0000, 0xffff} { }
};

struct Crc16Genibus : public CrcEngine<16, 0x1021, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xd64e;
  static constexpr const char* Name = "CRC-16/GENIBUS";
  Crc16Genibus() : CrcEngine{0xffff, 0xffff} { }
};

struct Crc16Gsm : public CrcEngine<16, 0x1021, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xce3c;
  static constexpr const char* Name = "CRC-16/GSM";
  Crc16Gsm() : CrcEngine{0x0000, 0xffff} { }
};

struct Crc16Ibm3740 : public CrcEngine<16, 0x1021, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x29b1;
  static constexpr const char* Name = "CRC-16/IBM-3740";
  Crc16Ibm3740() : CrcEngine{0xffff, 0x0000} { }
};

struct Crc16IbmSdlc : public CrcEngine<16, 0x1021, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x906e;
  static constexpr const char* Name = "CRC-16/IBM-SDLC";
  Crc16IbmSdlc() : CrcEngine{0xffff, 0xffff} { }
};

struct Crc16IsoIec144433A : public CrcEngine<16, 0x1021, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xbf05;
  static constexpr const char* Name = "CRC-16/ISO-IEC-14443-3-A";
  Crc16IsoIec144433A() : CrcEngine{0xc6c6, 0x0000} { }
};

struct Crc16Kermit : public CrcEngine<16, 0x1021, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x2189;
  static constexpr const char* Name = "CRC-16/KERMIT";
  Crc16Kermit() : CrcEngine{0x0000, 0x0000} { }
};

struct Crc16Lj1200 : public CrcEngine<16, 0x6f63, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xbdf4;
  static constexpr const char* Name = "CRC-16/LJ1200";
  Crc16Lj1200() : CrcEngine{0x0000, 0x0000} { }
};

struct Crc16M17 : public CrcEngine<16, 0x5935, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x772b;
  static constexpr const char* Name = "CRC-16/M17";
  Crc16M17() : CrcEngine{0xffff, 0x0000} { }
};

struct Crc16MaximDow : public CrcEngine<16, 0x8005, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x44c2;
  static constexpr const char* Name = "CRC-16/MAXIM-DOW";
  Crc16MaximDow() : CrcEngine{0x0000, 0xffff} { }
};

struct Crc16Mcrf4xx : public CrcEngine<16, 0x1021, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x6f91;
  static constexpr const char* Name = "CRC-16/MCRF4XX";
  Crc16Mcrf4xx() : CrcEngine{0xffff, 0x0000} { }
};

struct Crc16Modbus : public CrcEngine<16, 0x8005, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x4b37;
  static constexpr const char* Name = "CRC-16/MODBUS";
  Crc16Modbus() : CrcEngine{0xffff, 0x0000} { }
};

struct Crc16Nrsc5 : public CrcEngine<16, 0x080b, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xa066;
  static constexpr const char* Name = "CRC-16/NRSC-5";
  Crc16Nrsc5() : CrcEngine{0xffff, 0x0000} { }
};

struct Crc16OpensafetyA : public CrcEngine<16, 0x5935, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x5d38;
  static constexpr const char* Name = "CRC-16/OPENSAFETY-A";
  Crc16OpensafetyA() : CrcEngine{0x0000, 0x0000} { }
};

struct Crc16OpensafetyB : public CrcEngine<16, 0x755b, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x20fe;
  static constexpr const char* Name = "CRC-16/OPENSAFETY-B";
  Crc16OpensafetyB() : CrcEngine{0x0000, 0x0000} { }
};

struct Crc16Profibus : public CrcEngine<16, 0x1dcf, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xa819;
  static constexpr const char* Name = "CRC-16/PROFIBUS";
  Crc16Profibus() : CrcEngine{0xffff, 0xffff} { }
};

struct Crc16Riello : public CrcEngine<16, 0x1021, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x63d0;
  static constexpr const char* Name = "CRC-16/RIELLO";
  Crc16Riello() : CrcEngine{0xb2aa, 0x0000} { }
};

struct Crc16SpiFujitsu : public CrcEngine<16, 0x1021, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xe5cc;
  static constexpr const char* Name = "CRC-16/SPI-FUJITSU";
  Crc16SpiFujitsu() : CrcEngine{0x1d0f, 0x0000} { }
};

struct Crc16T10Dif : public CrcEngine<16, 0x8bb7, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xd0db;
  static constexpr const char* Name = "CRC-16/T10-DIF";
  Crc16T10Dif() : CrcEngine{0x0000, 0x0000} { }
};

struct Crc16Teledisk : public CrcEngine<16, 0xa097, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x0fb3;
  static constexpr const char* Name = "CRC-16/TELEDISK";
  Crc16Teledisk() : CrcEngine{0x0000, 0x0000} { }
};

struct Crc16Tms37157 : public CrcEngine<16, 0x1021, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x26b1;
  static constexpr const char* Name = "CRC-16/TMS37157";
  Crc16Tms37157() : CrcEngine{0x89ec, 0x0000} { }
};

struct Crc16Umts : public CrcEngine<16, 0x8005, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xfee8;
  static constexpr const char* Name = "CRC-16/UMTS";
  Crc16Umts() : CrcEngine{0x0000, 0x0000} { }
};

struct Crc16Usb : public CrcEngine<16, 0x8005, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xb4c8;
  static constexpr const char* Name = "CRC-16/USB";
  Crc16Usb() : CrcEngine{0xffff, 0xffff} { }
};

struct Crc16Xmodem : public CrcEngine<16, 0x1021, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x31c3;
  static constexpr const char* Name = "CRC-16/XMODEM";
  Crc16Xmodem() : CrcEngine{0x0000, 0x0000} { }
};

struct Crc17CanFd : public CrcEngine<17, 0x1685b, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x04f03;
  static constexpr const char* Name = "CRC-17/CAN-FD";
  Crc17CanFd() : CrcEngine{0x00000, 0x00000} { }
};

struct Crc21CanFd : public CrcEngine<21, 0x102899, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x0ed841;
  static constexpr const char* Name = "CRC-21/CAN-FD";
  Crc21CanFd() : CrcEngine{0x000000, 0x000000} { }
};

struct Crc24Ble : public CrcEngine<24, 0x00065b, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xc25a56;
  static constexpr const char* Name = "CRC-24/BLE";
  Crc24Ble() : CrcEngine{0x555555, 0x000000} { }
};

struct Crc24FlexrayA : public CrcEngine<24, 0x5d6dcb, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x7979bd;
  static constexpr const char* Name = "CRC-24/FLEXRAY-A";
  Crc24FlexrayA() : CrcEngine{0xfedcba, 0x000000} { }
};

struct Crc24FlexrayB : public CrcEngine<24, 0x5d6dcb, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x1f23b8;
  static constexpr const char* Name = "CRC-24/FLEXRAY-B";
  Crc24FlexrayB() : CrcEngine{0xabcdef, 0x000000} { }
};

struct Crc24Interlaken : public CrcEngine<24, 0x328b63, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xb4f3e6;
  static constexpr const char* Name = "CRC-24/INTERLAKEN";
  Crc24Interlaken() : CrcEngine{0xffffff, 0xffffff} { }
};

struct Crc24LteA : public CrcEngine<24, 0x864cfb, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xcde703;
  static constexpr const char* Name = "CRC-24/LTE-A";
  Crc24LteA() : CrcEngine{0x000000, 0x000000} { }
};

struct Crc24LteB : public CrcEngine<24, 0x800063, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x23ef52;
  static constexpr const char* Name = "CRC-24/LTE-B";
  Crc24LteB() : CrcEngine{0x000000, 0x000000} { }
};

struct Crc24Openpgp : public CrcEngine<24, 0x864cfb, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x21cf02;
  static constexpr const char* Name = "CRC-24/OPENPGP";
  Crc24Openpgp() : CrcEngine{0xb704ce, 0x000000} { }
};

struct Crc24Os9 : public CrcEngine<24, 0x800063, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x200fa5;
  static constexpr const char* Name = "CRC-24/OS-9";
  Crc24Os9() : CrcEngine{0xffffff, 0xffffff} { }
};

struct Crc30Cdma : public CrcEngine<30, 0x2030b9c7, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x04c34abf;
  static constexpr const char* Name = "CRC-30/CDMA";
  Crc30Cdma() : CrcEngine{0x3fffffff, 0x3fffffff} { }
};

struct Crc31Philips : public CrcEngine<31, 0x04c11db7, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x0ce9e46c;
  static constexpr const char* Name = "CRC-31/PHILIPS";
  Crc31Philips() : CrcEngine{0x7fffffff, 0x7fffffff} { }
};

struct Crc32Aixm : public CrcEngine<32, 0x814141ab, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x3010bf7f;
  static constexpr const char* Name = "CRC-32/AIXM";
  Crc32Aixm() : CrcEngine{0x00000000, 0x00000000} { }
};

struct Crc32Autosar : public CrcEngine<32, 0xf4acfb13, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x1697d06a;
  static constexpr const char* Name = "CRC-32/AUTOSAR";
  Crc32Autosar() : CrcEngine{0xffffffff, 0xffffffff} { }
};

struct Crc32Base91D : public CrcEngine<32, 0xa833982b, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x87315576;
  static constexpr const char* Name = "CRC-32/BASE91-D";
  Crc32Base91D() : CrcEngine{0xffffffff, 0xffffffff} { }
};

struct Crc32Bzip2 : public CrcEngine<32, 0x04c11db7, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xfc891918;
  static constexpr const char* Name = "CRC-32/BZIP2";
  Crc32Bzip2() : CrcEngine{0xffffffff, 0xffffffff} { }
};

struct Crc32CdRomEdc : public CrcEngine<32, 0x8001801b, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x6ec2edc4;
  static constexpr const char* Name = "CRC-32/CD-ROM-EDC";
  Crc32CdRomEdc() : CrcEngine{0x00000000, 0x00000000} { }
};

struct Crc32Cksum : public CrcEngine<32, 0x04c11db7, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x765e7680;
  static constexpr const char* Name = "CRC-32/CKSUM";
  Crc32Cksum() : CrcEngine{0x00000000, 0xffffffff} { }
};

struct Crc32Iscsi : public CrcEngine<32, 0x1edc6f41, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xe3069283;
  static constexpr const char* Name = "CRC-32/ISCSI";
  Crc32Iscsi() : CrcEngine{0xffffffff, 0xffffffff} { }
};

struct Crc32IsoHdlc : public CrcEngine<32, 0x04c11db7, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xcbf43926;
  static constexpr const char* Name = "CRC-32/ISO-HDLC";
  Crc32IsoHdlc() : CrcEngine{0xffffffff, 0xffffffff} { }
};

struct Crc32Jamcrc : public CrcEngine<32, 0x04c11db7, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x340bc6d9;
  static constexpr const char* Name = "CRC-32/JAMCRC";
  Crc32Jamcrc() : CrcEngine{0xffffffff, 0x00000000} { }
};

struct Crc32Mef : public CrcEngine<32, 0x741b8cd7, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xd2c22f51;
  static constexpr const char* Name = "CRC-32/MEF";
  Crc32Mef() : CrcEngine{0xffffffff, 0x00000000} { }
};

struct Crc32Mpeg2 : public CrcEngine<32, 0x04c11db7, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x0376e6e7;
  static constexpr const char* Name = "CRC-32/MPEG-2";
  Crc32Mpeg2() : CrcEngine{0xffffffff, 0x00000000} { }
};

struct Crc32Xfer : public CrcEngine<32, 0x000000af, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xbd0be338;
  static constexpr const char* Name = "CRC-32/XFER";
  Crc32Xfer() : CrcEngine{0x00000000, 0x00000000} { }
};

struct Crc40Gsm : public CrcEngine<40, 0x0004820009, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0xd4164fc646;
  static constexpr const char* Name = "CRC-40/GSM";
  Crc40Gsm() : CrcEngine{0x0000000000, 0xffffffffff} { }
};

struct Crc64Ecma182 : public CrcEngine<64, 0x42f0e1eba9ea3693, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x6c40df5f0b497347;
  static constexpr const char* Name = "CRC-64/ECMA-182";
  Crc64Ecma182() : CrcEngine{0x0000000000000000, 0x0000000000000000} { }
};

struct Crc64GoIso : public CrcEngine<64, 0x000000000000001b, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xb90956c775a41001;
  static constexpr const char* Name = "CRC-64/GO-ISO";
  Crc64GoIso() : CrcEngine{0xffffffffffffffff, 0xffffffffffffffff} { }
};

struct Crc64Ms : public CrcEngine<64, 0x259c84cba6426349, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x75d4b74f024eceea;
  static constexpr const char* Name = "CRC-64/MS";
  Crc64Ms() : CrcEngine{0xffffffffffffffff, 0x0000000000000000} { }
};

struct Crc64Nvme : public CrcEngine<64, 0xad93d23594c93659, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xae8b14860a799888;
  static constexpr const char* Name = "CRC-64/NVME";
  Crc64Nvme() : CrcEngine{0xffffffffffffffff, 0xffffffffffffffff} { }
};

struct Crc64Redis : public CrcEngine<64, 0xad93d23594c935a9, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0xe9c6d914c4b8d9ca;
  static constexpr const char* Name = "CRC-64/REDIS";
  Crc64Redis() : CrcEngine{0x0000000000000000, 0x0000000000000000} { }
};

struct Crc64We : public CrcEngine<64, 0x42f0e1eba9ea3693, CrcDir::MsbFirst, Slices> {
  static constexpr CrcType Check = 0x62ec59e3f1a4f00a;
  static constexpr const char* Name = "CRC-64/WE";
  Crc64We() : CrcEngine{0xffffffffffffffff, 0xffffffffffffffff} { }
};

struct Crc64Xz : public CrcEngine<64, 0x42f0e1eba9ea3693, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x995dc9bbdf1939fa;
  static constexpr const char* Name = "CRC-64/XZ";
  Crc64Xz() : CrcEngine{0xffffffffffffffff, 0xffffffffffffffff} { }
};

#if 0
struct Crc82Darc : public CrcEngine<82, 0x0308c0111011401440411, CrcDir::LsbFirst, Slices> {
  static constexpr CrcType Check = 0x09ea83f625023801fd612;
  static constexpr const char* Name = "CRC-82/DARC";
  Crc82Darc() : CrcEngine{0x000000000000000000000, 0x000000000000000000000} { }
};
#endif

using AllCrcAlgorithms = meta::TypeList<
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
  // Crc82Darc
>; // AllCrcAlgorithms

} // tjg
