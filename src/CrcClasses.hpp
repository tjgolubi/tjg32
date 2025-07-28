/// @see https://reveng.sourceforge.io/crc-catalogue/all.htm

struct CrcCrc3Gsm : public CrcEngine<3, 0x3, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x4;
  static constexpr const char* Name = "CRC-3/GSM";
  CrcCrc3Gsm() : CrcEngine{0x0, 0x7} { }
};

struct CrcCrc3Rohc : public CrcEngine<3, 0x3, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x6;
  static constexpr const char* Name = "CRC-3/ROHC";
  CrcCrc3Rohc() : CrcEngine{0x7, 0x0} { }
};

struct CrcCrc4G704 : public CrcEngine<4, 0x3, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x7;
  static constexpr const char* Name = "CRC-4/G-704";
  CrcCrc4G704() : CrcEngine{0x0, 0x0} { }
};

struct CrcCrc4Interlaken : public CrcEngine<4, 0x3, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xb;
  static constexpr const char* Name = "CRC-4/INTERLAKEN";
  CrcCrc4Interlaken() : CrcEngine{0xf, 0xf} { }
};

struct CrcCrc5EpcC1g2 : public CrcEngine<5, 0x09, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x00;
  static constexpr const char* Name = "CRC-5/EPC-C1G2";
  CrcCrc5EpcC1g2() : CrcEngine{0x09, 0x00} { }
};

struct CrcCrc5G704 : public CrcEngine<5, 0x15, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x07;
  static constexpr const char* Name = "CRC-5/G-704";
  CrcCrc5G704() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc5Usb : public CrcEngine<5, 0x05, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x19;
  static constexpr const char* Name = "CRC-5/USB";
  CrcCrc5Usb() : CrcEngine{0x1f, 0x1f} { }
};

struct CrcCrc6Cdma2000A : public CrcEngine<6, 0x27, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x0d;
  static constexpr const char* Name = "CRC-6/CDMA2000-A";
  CrcCrc6Cdma2000A() : CrcEngine{0x3f, 0x00} { }
};

struct CrcCrc6Cdma2000B : public CrcEngine<6, 0x07, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x3b;
  static constexpr const char* Name = "CRC-6/CDMA2000-B";
  CrcCrc6Cdma2000B() : CrcEngine{0x3f, 0x00} { }
};

struct CrcCrc6Darc : public CrcEngine<6, 0x19, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x26;
  static constexpr const char* Name = "CRC-6/DARC";
  CrcCrc6Darc() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc6G704 : public CrcEngine<6, 0x03, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x06;
  static constexpr const char* Name = "CRC-6/G-704";
  CrcCrc6G704() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc6Gsm : public CrcEngine<6, 0x2f, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x13;
  static constexpr const char* Name = "CRC-6/GSM";
  CrcCrc6Gsm() : CrcEngine{0x00, 0x3f} { }
};

struct CrcCrc7Mmc : public CrcEngine<7, 0x09, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x75;
  static constexpr const char* Name = "CRC-7/MMC";
  CrcCrc7Mmc() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc7Rohc : public CrcEngine<7, 0x4f, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x53;
  static constexpr const char* Name = "CRC-7/ROHC";
  CrcCrc7Rohc() : CrcEngine{0x7f, 0x00} { }
};

struct CrcCrc7Umts : public CrcEngine<7, 0x45, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x61;
  static constexpr const char* Name = "CRC-7/UMTS";
  CrcCrc7Umts() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc8Autosar : public CrcEngine<8, 0x2f, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xdf;
  static constexpr const char* Name = "CRC-8/AUTOSAR";
  CrcCrc8Autosar() : CrcEngine{0xff, 0xff} { }
};

struct CrcCrc8Bluetooth : public CrcEngine<8, 0xa7, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x26;
  static constexpr const char* Name = "CRC-8/BLUETOOTH";
  CrcCrc8Bluetooth() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc8Cdma2000 : public CrcEngine<8, 0x9b, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xda;
  static constexpr const char* Name = "CRC-8/CDMA2000";
  CrcCrc8Cdma2000() : CrcEngine{0xff, 0x00} { }
};

struct CrcCrc8Darc : public CrcEngine<8, 0x39, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x15;
  static constexpr const char* Name = "CRC-8/DARC";
  CrcCrc8Darc() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc8DvbS2 : public CrcEngine<8, 0xd5, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xbc;
  static constexpr const char* Name = "CRC-8/DVB-S2";
  CrcCrc8DvbS2() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc8GsmA : public CrcEngine<8, 0x1d, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x37;
  static constexpr const char* Name = "CRC-8/GSM-A";
  CrcCrc8GsmA() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc8GsmB : public CrcEngine<8, 0x49, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x94;
  static constexpr const char* Name = "CRC-8/GSM-B";
  CrcCrc8GsmB() : CrcEngine{0x00, 0xff} { }
};

struct CrcCrc8Hitag : public CrcEngine<8, 0x1d, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xb4;
  static constexpr const char* Name = "CRC-8/HITAG";
  CrcCrc8Hitag() : CrcEngine{0xff, 0x00} { }
};

struct CrcCrc8I4321 : public CrcEngine<8, 0x07, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xa1;
  static constexpr const char* Name = "CRC-8/I-432-1";
  CrcCrc8I4321() : CrcEngine{0x00, 0x55} { }
};

struct CrcCrc8ICode : public CrcEngine<8, 0x1d, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x7e;
  static constexpr const char* Name = "CRC-8/I-CODE";
  CrcCrc8ICode() : CrcEngine{0xfd, 0x00} { }
};

struct CrcCrc8Lte : public CrcEngine<8, 0x9b, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xea;
  static constexpr const char* Name = "CRC-8/LTE";
  CrcCrc8Lte() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc8MaximDow : public CrcEngine<8, 0x31, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xa1;
  static constexpr const char* Name = "CRC-8/MAXIM-DOW";
  CrcCrc8MaximDow() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc8MifareMad : public CrcEngine<8, 0x1d, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x99;
  static constexpr const char* Name = "CRC-8/MIFARE-MAD";
  CrcCrc8MifareMad() : CrcEngine{0xc7, 0x00} { }
};

struct CrcCrc8Nrsc5 : public CrcEngine<8, 0x31, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xf7;
  static constexpr const char* Name = "CRC-8/NRSC-5";
  CrcCrc8Nrsc5() : CrcEngine{0xff, 0x00} { }
};

struct CrcCrc8Opensafety : public CrcEngine<8, 0x2f, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x3e;
  static constexpr const char* Name = "CRC-8/OPENSAFETY";
  CrcCrc8Opensafety() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc8Rohc : public CrcEngine<8, 0x07, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xd0;
  static constexpr const char* Name = "CRC-8/ROHC";
  CrcCrc8Rohc() : CrcEngine{0xff, 0x00} { }
};

struct CrcCrc8SaeJ1850 : public CrcEngine<8, 0x1d, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x4b;
  static constexpr const char* Name = "CRC-8/SAE-J1850";
  CrcCrc8SaeJ1850() : CrcEngine{0xff, 0xff} { }
};

struct CrcCrc8Smbus : public CrcEngine<8, 0x07, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xf4;
  static constexpr const char* Name = "CRC-8/SMBUS";
  CrcCrc8Smbus() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc8Tech3250 : public CrcEngine<8, 0x1d, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x97;
  static constexpr const char* Name = "CRC-8/TECH-3250";
  CrcCrc8Tech3250() : CrcEngine{0xff, 0x00} { }
};

struct CrcCrc8Wcdma : public CrcEngine<8, 0x9b, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x25;
  static constexpr const char* Name = "CRC-8/WCDMA";
  CrcCrc8Wcdma() : CrcEngine{0x00, 0x00} { }
};

struct CrcCrc10Atm : public CrcEngine<10, 0x233, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x199;
  static constexpr const char* Name = "CRC-10/ATM";
  CrcCrc10Atm() : CrcEngine{0x000, 0x000} { }
};

struct CrcCrc10Cdma2000 : public CrcEngine<10, 0x3d9, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x233;
  static constexpr const char* Name = "CRC-10/CDMA2000";
  CrcCrc10Cdma2000() : CrcEngine{0x3ff, 0x000} { }
};

struct CrcCrc10Gsm : public CrcEngine<10, 0x175, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x12a;
  static constexpr const char* Name = "CRC-10/GSM";
  CrcCrc10Gsm() : CrcEngine{0x000, 0x3ff} { }
};

struct CrcCrc11Flexray : public CrcEngine<11, 0x385, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x5a3;
  static constexpr const char* Name = "CRC-11/FLEXRAY";
  CrcCrc11Flexray() : CrcEngine{0x01a, 0x000} { }
};

struct CrcCrc11Umts : public CrcEngine<11, 0x307, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x061;
  static constexpr const char* Name = "CRC-11/UMTS";
  CrcCrc11Umts() : CrcEngine{0x000, 0x000} { }
};

struct CrcCrc12Cdma2000 : public CrcEngine<12, 0xf13, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xd4d;
  static constexpr const char* Name = "CRC-12/CDMA2000";
  CrcCrc12Cdma2000() : CrcEngine{0xfff, 0x000} { }
};

struct CrcCrc12Dect : public CrcEngine<12, 0x80f, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xf5b;
  static constexpr const char* Name = "CRC-12/DECT";
  CrcCrc12Dect() : CrcEngine{0x000, 0x000} { }
};

struct CrcCrc12Gsm : public CrcEngine<12, 0xd31, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xb34;
  static constexpr const char* Name = "CRC-12/GSM";
  CrcCrc12Gsm() : CrcEngine{0x000, 0xfff} { }
};

#if 0
struct CrcCrc12Umts : public CrcEngine<12, 0x80f, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xdaf;
  static constexpr const char* Name = "CRC-12/UMTS";
  CrcCrc12Umts() : CrcEngine{0x000, 0x000} { }
  crc_type value() const
    { return detail::reflect_bits(CrcEngine::value(), 12); }
};
#endif

struct CrcCrc13Bbc : public CrcEngine<13, 0x1cf5, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x04fa;
  static constexpr const char* Name = "CRC-13/BBC";
  CrcCrc13Bbc() : CrcEngine{0x0000, 0x0000} { }
};

struct CrcCrc14Darc : public CrcEngine<14, 0x0805, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x082d;
  static constexpr const char* Name = "CRC-14/DARC";
  CrcCrc14Darc() : CrcEngine{0x0000, 0x0000} { }
};

struct CrcCrc14Gsm : public CrcEngine<14, 0x202d, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x30ae;
  static constexpr const char* Name = "CRC-14/GSM";
  CrcCrc14Gsm() : CrcEngine{0x0000, 0x3fff} { }
};

struct CrcCrc15Can : public CrcEngine<15, 0x4599, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x059e;
  static constexpr const char* Name = "CRC-15/CAN";
  CrcCrc15Can() : CrcEngine{0x0000, 0x0000} { }
};

struct CrcCrc15Mpt1327 : public CrcEngine<15, 0x6815, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x2566;
  static constexpr const char* Name = "CRC-15/MPT1327";
  CrcCrc15Mpt1327() : CrcEngine{0x0000, 0x0001} { }
};

struct CrcCrc16Arc : public CrcEngine<16, 0x8005, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xbb3d;
  static constexpr const char* Name = "CRC-16/ARC";
  CrcCrc16Arc() : CrcEngine{0x0000, 0x0000} { }
};

struct CrcCrc16Cdma2000 : public CrcEngine<16, 0xc867, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x4c06;
  static constexpr const char* Name = "CRC-16/CDMA2000";
  CrcCrc16Cdma2000() : CrcEngine{0xffff, 0x0000} { }
};

struct CrcCrc16Cms : public CrcEngine<16, 0x8005, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xaee7;
  static constexpr const char* Name = "CRC-16/CMS";
  CrcCrc16Cms() : CrcEngine{0xffff, 0x0000} { }
};

struct CrcCrc16Dds110 : public CrcEngine<16, 0x8005, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x9ecf;
  static constexpr const char* Name = "CRC-16/DDS-110";
  CrcCrc16Dds110() : CrcEngine{0x800d, 0x0000} { }
};

struct CrcCrc16DectR : public CrcEngine<16, 0x0589, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x007e;
  static constexpr const char* Name = "CRC-16/DECT-R";
  CrcCrc16DectR() : CrcEngine{0x0000, 0x0001} { }
};

struct CrcCrc16DectX : public CrcEngine<16, 0x0589, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x007f;
  static constexpr const char* Name = "CRC-16/DECT-X";
  CrcCrc16DectX() : CrcEngine{0x0000, 0x0000} { }
};

struct CrcCrc16Dnp : public CrcEngine<16, 0x3d65, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xea82;
  static constexpr const char* Name = "CRC-16/DNP";
  CrcCrc16Dnp() : CrcEngine{0x0000, 0xffff} { }
};

struct CrcCrc16En13757 : public CrcEngine<16, 0x3d65, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xc2b7;
  static constexpr const char* Name = "CRC-16/EN-13757";
  CrcCrc16En13757() : CrcEngine{0x0000, 0xffff} { }
};

struct CrcCrc16Genibus : public CrcEngine<16, 0x1021, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xd64e;
  static constexpr const char* Name = "CRC-16/GENIBUS";
  CrcCrc16Genibus() : CrcEngine{0xffff, 0xffff} { }
};

struct CrcCrc16Gsm : public CrcEngine<16, 0x1021, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xce3c;
  static constexpr const char* Name = "CRC-16/GSM";
  CrcCrc16Gsm() : CrcEngine{0x0000, 0xffff} { }
};

struct CrcCrc16Ibm3740 : public CrcEngine<16, 0x1021, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x29b1;
  static constexpr const char* Name = "CRC-16/IBM-3740";
  CrcCrc16Ibm3740() : CrcEngine{0xffff, 0x0000} { }
};

struct CrcCrc16IbmSdlc : public CrcEngine<16, 0x1021, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x906e;
  static constexpr const char* Name = "CRC-16/IBM-SDLC";
  CrcCrc16IbmSdlc() : CrcEngine{0xffff, 0xffff} { }
};

struct CrcCrc16IsoIec144433A : public CrcEngine<16, 0x1021, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xbf05;
  static constexpr const char* Name = "CRC-16/ISO-IEC-14443-3-A";
  CrcCrc16IsoIec144433A() : CrcEngine{0xc6c6, 0x0000} { }
};

struct CrcCrc16Kermit : public CrcEngine<16, 0x1021, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x2189;
  static constexpr const char* Name = "CRC-16/KERMIT";
  CrcCrc16Kermit() : CrcEngine{0x0000, 0x0000} { }
};

struct CrcCrc16Lj1200 : public CrcEngine<16, 0x6f63, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xbdf4;
  static constexpr const char* Name = "CRC-16/LJ1200";
  CrcCrc16Lj1200() : CrcEngine{0x0000, 0x0000} { }
};

struct CrcCrc16M17 : public CrcEngine<16, 0x5935, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x772b;
  static constexpr const char* Name = "CRC-16/M17";
  CrcCrc16M17() : CrcEngine{0xffff, 0x0000} { }
};

struct CrcCrc16MaximDow : public CrcEngine<16, 0x8005, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x44c2;
  static constexpr const char* Name = "CRC-16/MAXIM-DOW";
  CrcCrc16MaximDow() : CrcEngine{0x0000, 0xffff} { }
};

struct CrcCrc16Mcrf4xx : public CrcEngine<16, 0x1021, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x6f91;
  static constexpr const char* Name = "CRC-16/MCRF4XX";
  CrcCrc16Mcrf4xx() : CrcEngine{0xffff, 0x0000} { }
};

struct CrcCrc16Modbus : public CrcEngine<16, 0x8005, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x4b37;
  static constexpr const char* Name = "CRC-16/MODBUS";
  CrcCrc16Modbus() : CrcEngine{0xffff, 0x0000} { }
};

struct CrcCrc16Nrsc5 : public CrcEngine<16, 0x080b, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xa066;
  static constexpr const char* Name = "CRC-16/NRSC-5";
  CrcCrc16Nrsc5() : CrcEngine{0xffff, 0x0000} { }
};

struct CrcCrc16OpensafetyA : public CrcEngine<16, 0x5935, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x5d38;
  static constexpr const char* Name = "CRC-16/OPENSAFETY-A";
  CrcCrc16OpensafetyA() : CrcEngine{0x0000, 0x0000} { }
};

struct CrcCrc16OpensafetyB : public CrcEngine<16, 0x755b, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x20fe;
  static constexpr const char* Name = "CRC-16/OPENSAFETY-B";
  CrcCrc16OpensafetyB() : CrcEngine{0x0000, 0x0000} { }
};

struct CrcCrc16Profibus : public CrcEngine<16, 0x1dcf, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xa819;
  static constexpr const char* Name = "CRC-16/PROFIBUS";
  CrcCrc16Profibus() : CrcEngine{0xffff, 0xffff} { }
};

struct CrcCrc16Riello : public CrcEngine<16, 0x1021, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x63d0;
  static constexpr const char* Name = "CRC-16/RIELLO";
  CrcCrc16Riello() : CrcEngine{0xb2aa, 0x0000} { }
};

struct CrcCrc16SpiFujitsu : public CrcEngine<16, 0x1021, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xe5cc;
  static constexpr const char* Name = "CRC-16/SPI-FUJITSU";
  CrcCrc16SpiFujitsu() : CrcEngine{0x1d0f, 0x0000} { }
};

struct CrcCrc16T10Dif : public CrcEngine<16, 0x8bb7, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xd0db;
  static constexpr const char* Name = "CRC-16/T10-DIF";
  CrcCrc16T10Dif() : CrcEngine{0x0000, 0x0000} { }
};

struct CrcCrc16Teledisk : public CrcEngine<16, 0xa097, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x0fb3;
  static constexpr const char* Name = "CRC-16/TELEDISK";
  CrcCrc16Teledisk() : CrcEngine{0x0000, 0x0000} { }
};

struct CrcCrc16Tms37157 : public CrcEngine<16, 0x1021, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x26b1;
  static constexpr const char* Name = "CRC-16/TMS37157";
  CrcCrc16Tms37157() : CrcEngine{0x89ec, 0x0000} { }
};

struct CrcCrc16Umts : public CrcEngine<16, 0x8005, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xfee8;
  static constexpr const char* Name = "CRC-16/UMTS";
  CrcCrc16Umts() : CrcEngine{0x0000, 0x0000} { }
};

struct CrcCrc16Usb : public CrcEngine<16, 0x8005, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xb4c8;
  static constexpr const char* Name = "CRC-16/USB";
  CrcCrc16Usb() : CrcEngine{0xffff, 0xffff} { }
};

struct CrcCrc16Xmodem : public CrcEngine<16, 0x1021, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x31c3;
  static constexpr const char* Name = "CRC-16/XMODEM";
  CrcCrc16Xmodem() : CrcEngine{0x0000, 0x0000} { }
};

struct CrcCrc17CanFd : public CrcEngine<17, 0x1685b, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x04f03;
  static constexpr const char* Name = "CRC-17/CAN-FD";
  CrcCrc17CanFd() : CrcEngine{0x00000, 0x00000} { }
};

struct CrcCrc21CanFd : public CrcEngine<21, 0x102899, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x0ed841;
  static constexpr const char* Name = "CRC-21/CAN-FD";
  CrcCrc21CanFd() : CrcEngine{0x000000, 0x000000} { }
};

struct CrcCrc24Ble : public CrcEngine<24, 0x00065b, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xc25a56;
  static constexpr const char* Name = "CRC-24/BLE";
  CrcCrc24Ble() : CrcEngine{0x555555, 0x000000} { }
};

struct CrcCrc24FlexrayA : public CrcEngine<24, 0x5d6dcb, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x7979bd;
  static constexpr const char* Name = "CRC-24/FLEXRAY-A";
  CrcCrc24FlexrayA() : CrcEngine{0xfedcba, 0x000000} { }
};

struct CrcCrc24FlexrayB : public CrcEngine<24, 0x5d6dcb, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x1f23b8;
  static constexpr const char* Name = "CRC-24/FLEXRAY-B";
  CrcCrc24FlexrayB() : CrcEngine{0xabcdef, 0x000000} { }
};

struct CrcCrc24Interlaken : public CrcEngine<24, 0x328b63, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xb4f3e6;
  static constexpr const char* Name = "CRC-24/INTERLAKEN";
  CrcCrc24Interlaken() : CrcEngine{0xffffff, 0xffffff} { }
};

struct CrcCrc24LteA : public CrcEngine<24, 0x864cfb, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xcde703;
  static constexpr const char* Name = "CRC-24/LTE-A";
  CrcCrc24LteA() : CrcEngine{0x000000, 0x000000} { }
};

struct CrcCrc24LteB : public CrcEngine<24, 0x800063, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x23ef52;
  static constexpr const char* Name = "CRC-24/LTE-B";
  CrcCrc24LteB() : CrcEngine{0x000000, 0x000000} { }
};

struct CrcCrc24Openpgp : public CrcEngine<24, 0x864cfb, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x21cf02;
  static constexpr const char* Name = "CRC-24/OPENPGP";
  CrcCrc24Openpgp() : CrcEngine{0xb704ce, 0x000000} { }
};

struct CrcCrc24Os9 : public CrcEngine<24, 0x800063, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x200fa5;
  static constexpr const char* Name = "CRC-24/OS-9";
  CrcCrc24Os9() : CrcEngine{0xffffff, 0xffffff} { }
};

struct CrcCrc30Cdma : public CrcEngine<30, 0x2030b9c7, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x04c34abf;
  static constexpr const char* Name = "CRC-30/CDMA";
  CrcCrc30Cdma() : CrcEngine{0x3fffffff, 0x3fffffff} { }
};

struct CrcCrc31Philips : public CrcEngine<31, 0x04c11db7, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x0ce9e46c;
  static constexpr const char* Name = "CRC-31/PHILIPS";
  CrcCrc31Philips() : CrcEngine{0x7fffffff, 0x7fffffff} { }
};

struct CrcCrc32Aixm : public CrcEngine<32, 0x814141ab, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x3010bf7f;
  static constexpr const char* Name = "CRC-32/AIXM";
  CrcCrc32Aixm() : CrcEngine{0x00000000, 0x00000000} { }
};

struct CrcCrc32Autosar : public CrcEngine<32, 0xf4acfb13, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x1697d06a;
  static constexpr const char* Name = "CRC-32/AUTOSAR";
  CrcCrc32Autosar() : CrcEngine{0xffffffff, 0xffffffff} { }
};

struct CrcCrc32Base91D : public CrcEngine<32, 0xa833982b, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x87315576;
  static constexpr const char* Name = "CRC-32/BASE91-D";
  CrcCrc32Base91D() : CrcEngine{0xffffffff, 0xffffffff} { }
};

struct CrcCrc32Bzip2 : public CrcEngine<32, 0x04c11db7, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xfc891918;
  static constexpr const char* Name = "CRC-32/BZIP2";
  CrcCrc32Bzip2() : CrcEngine{0xffffffff, 0xffffffff} { }
};

struct CrcCrc32CdRomEdc : public CrcEngine<32, 0x8001801b, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x6ec2edc4;
  static constexpr const char* Name = "CRC-32/CD-ROM-EDC";
  CrcCrc32CdRomEdc() : CrcEngine{0x00000000, 0x00000000} { }
};

struct CrcCrc32Cksum : public CrcEngine<32, 0x04c11db7, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x765e7680;
  static constexpr const char* Name = "CRC-32/CKSUM";
  CrcCrc32Cksum() : CrcEngine{0x00000000, 0xffffffff} { }
};

struct CrcCrc32Iscsi : public CrcEngine<32, 0x1edc6f41, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xe3069283;
  static constexpr const char* Name = "CRC-32/ISCSI";
  CrcCrc32Iscsi() : CrcEngine{0xffffffff, 0xffffffff} { }
};

struct CrcCrc32IsoHdlc : public CrcEngine<32, 0x04c11db7, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xcbf43926;
  static constexpr const char* Name = "CRC-32/ISO-HDLC";
  CrcCrc32IsoHdlc() : CrcEngine{0xffffffff, 0xffffffff} { }
};

struct CrcCrc32Jamcrc : public CrcEngine<32, 0x04c11db7, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x340bc6d9;
  static constexpr const char* Name = "CRC-32/JAMCRC";
  CrcCrc32Jamcrc() : CrcEngine{0xffffffff, 0x00000000} { }
};

struct CrcCrc32Mef : public CrcEngine<32, 0x741b8cd7, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xd2c22f51;
  static constexpr const char* Name = "CRC-32/MEF";
  CrcCrc32Mef() : CrcEngine{0xffffffff, 0x00000000} { }
};

struct CrcCrc32Mpeg2 : public CrcEngine<32, 0x04c11db7, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x0376e6e7;
  static constexpr const char* Name = "CRC-32/MPEG-2";
  CrcCrc32Mpeg2() : CrcEngine{0xffffffff, 0x00000000} { }
};

struct CrcCrc32Xfer : public CrcEngine<32, 0x000000af, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xbd0be338;
  static constexpr const char* Name = "CRC-32/XFER";
  CrcCrc32Xfer() : CrcEngine{0x00000000, 0x00000000} { }
};

struct CrcCrc40Gsm : public CrcEngine<40, 0x0004820009, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0xd4164fc646;
  static constexpr const char* Name = "CRC-40/GSM";
  CrcCrc40Gsm() : CrcEngine{0x0000000000, 0xffffffffff} { }
};

struct CrcCrc64Ecma182 : public CrcEngine<64, 0x42f0e1eba9ea3693, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x6c40df5f0b497347;
  static constexpr const char* Name = "CRC-64/ECMA-182";
  CrcCrc64Ecma182() : CrcEngine{0x0000000000000000, 0x0000000000000000} { }
};

struct CrcCrc64GoIso : public CrcEngine<64, 0x000000000000001b, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xb90956c775a41001;
  static constexpr const char* Name = "CRC-64/GO-ISO";
  CrcCrc64GoIso() : CrcEngine{0xffffffffffffffff, 0xffffffffffffffff} { }
};

struct CrcCrc64Ms : public CrcEngine<64, 0x259c84cba6426349, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x75d4b74f024eceea;
  static constexpr const char* Name = "CRC-64/MS";
  CrcCrc64Ms() : CrcEngine{0xffffffffffffffff, 0x0000000000000000} { }
};

struct CrcCrc64Nvme : public CrcEngine<64, 0xad93d23594c93659, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xae8b14860a799888;
  static constexpr const char* Name = "CRC-64/NVME";
  CrcCrc64Nvme() : CrcEngine{0xffffffffffffffff, 0xffffffffffffffff} { }
};

struct CrcCrc64Redis : public CrcEngine<64, 0xad93d23594c935a9, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0xe9c6d914c4b8d9ca;
  static constexpr const char* Name = "CRC-64/REDIS";
  CrcCrc64Redis() : CrcEngine{0x0000000000000000, 0x0000000000000000} { }
};

struct CrcCrc64We : public CrcEngine<64, 0x42f0e1eba9ea3693, CrcDir::MsbFirst> {
  static constexpr crc_type Check = 0x62ec59e3f1a4f00a;
  static constexpr const char* Name = "CRC-64/WE";
  CrcCrc64We() : CrcEngine{0xffffffffffffffff, 0xffffffffffffffff} { }
};

struct CrcCrc64Xz : public CrcEngine<64, 0x42f0e1eba9ea3693, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x995dc9bbdf1939fa;
  static constexpr const char* Name = "CRC-64/XZ";
  CrcCrc64Xz() : CrcEngine{0xffffffffffffffff, 0xffffffffffffffff} { }
};

struct CrcCrc82Darc : public CrcEngine<82, 0x0308c0111011401440411, CrcDir::LsbFirst> {
  static constexpr crc_type Check = 0x09ea83f625023801fd612;
  static constexpr const char* Name = "CRC-82/DARC";
  CrcCrc82Darc() : CrcEngine{0x000000000000000000000, 0x000000000000000000000} { }
};

using AllCrcAlgorithms = meta::TypeList<
  CrcCrc3Gsm,
  CrcCrc3Rohc,
  CrcCrc4G704,
  CrcCrc4Interlaken,
  CrcCrc5EpcC1g2,
  CrcCrc5G704,
  CrcCrc5Usb,
  CrcCrc6Cdma2000A,
  CrcCrc6Cdma2000B,
  CrcCrc6Darc,
  CrcCrc6G704,
  CrcCrc6Gsm,
  CrcCrc7Mmc,
  CrcCrc7Rohc,
  CrcCrc7Umts,
  CrcCrc8Autosar,
  CrcCrc8Bluetooth,
  CrcCrc8Cdma2000,
  CrcCrc8Darc,
  CrcCrc8DvbS2,
  CrcCrc8GsmA,
  CrcCrc8GsmB,
  CrcCrc8Hitag,
  CrcCrc8I4321,
  CrcCrc8ICode,
  CrcCrc8Lte,
  CrcCrc8MaximDow,
  CrcCrc8MifareMad,
  CrcCrc8Nrsc5,
  CrcCrc8Opensafety,
  CrcCrc8Rohc,
  CrcCrc8SaeJ1850,
  CrcCrc8Smbus,
  CrcCrc8Tech3250,
  CrcCrc8Wcdma,
  CrcCrc10Atm,
  CrcCrc10Cdma2000,
  CrcCrc10Gsm,
  CrcCrc11Flexray,
  CrcCrc11Umts,
  CrcCrc12Cdma2000,
  CrcCrc12Dect,
  CrcCrc12Gsm,
  CrcCrc12Umts,
  CrcCrc13Bbc,
  CrcCrc14Darc,
  CrcCrc14Gsm,
  CrcCrc15Can,
  CrcCrc15Mpt1327,
  CrcCrc16Arc,
  CrcCrc16Cdma2000,
  CrcCrc16Cms,
  CrcCrc16Dds110,
  CrcCrc16DectR,
  CrcCrc16DectX,
  CrcCrc16Dnp,
  CrcCrc16En13757,
  CrcCrc16Genibus,
  CrcCrc16Gsm,
  CrcCrc16Ibm3740,
  CrcCrc16IbmSdlc,
  CrcCrc16IsoIec144433A,
  CrcCrc16Kermit,
  CrcCrc16Lj1200,
  CrcCrc16M17,
  CrcCrc16MaximDow,
  CrcCrc16Mcrf4xx,
  CrcCrc16Modbus,
  CrcCrc16Nrsc5,
  CrcCrc16OpensafetyA,
  CrcCrc16OpensafetyB,
  CrcCrc16Profibus,
  CrcCrc16Riello,
  CrcCrc16SpiFujitsu,
  CrcCrc16T10Dif,
  CrcCrc16Teledisk,
  CrcCrc16Tms37157,
  CrcCrc16Umts,
  CrcCrc16Usb,
  CrcCrc16Xmodem,
  CrcCrc17CanFd,
  CrcCrc21CanFd,
  CrcCrc24Ble,
  CrcCrc24FlexrayA,
  CrcCrc24FlexrayB,
  CrcCrc24Interlaken,
  CrcCrc24LteA,
  CrcCrc24LteB,
  CrcCrc24Openpgp,
  CrcCrc24Os9,
  CrcCrc30Cdma,
  CrcCrc31Philips,
  CrcCrc32Aixm,
  CrcCrc32Autosar,
  CrcCrc32Base91D,
  CrcCrc32Bzip2,
  CrcCrc32CdRomEdc,
  CrcCrc32Cksum,
  CrcCrc32Iscsi,
  CrcCrc32IsoHdlc,
  CrcCrc32Jamcrc,
  CrcCrc32Mef,
  CrcCrc32Mpeg2,
  CrcCrc32Xfer,
  CrcCrc40Gsm,
  CrcCrc64Ecma182,
  CrcCrc64GoIso,
  CrcCrc64Ms,
  CrcCrc64Nvme,
  CrcCrc64Redis,
  CrcCrc64We,
  CrcCrc64Xz,
  CrcCrc82Darc
>; // AllCrcAlgorithms
