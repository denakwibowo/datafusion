#include<pch.h>
#include<stdio.h>
#include<stdlib.h>
#include <boost/algorithm/string.hpp>
#include<iostream>
#include <vector>
#include <string>
#include "Parsingasterix10.h"

struct partial_asterix {
	std::vector<std::string> asterix_take;
	std::vector<std::string> asterix_remain;
};

struct data_item {
	std::vector<std::string> i010;
	std::vector<std::string> i000;
	std::vector<std::string> i020;
	std::vector<std::string> i140;
	std::vector<std::string> i041;
	std::vector<std::string> i040;
	std::vector<std::string> i042;
	std::vector<std::string> i200;
	std::vector<std::string> i202;
	std::vector<std::string> i161;
	std::vector<std::string> i170;
	std::vector<std::string> i060;
	std::vector<std::string> i220;
	std::vector<std::string> i245;
	std::vector<std::string> i250;
	std::vector<std::string> i300;
	std::vector<std::string> i090;
	std::vector<std::string> i091;
	std::vector<std::string> i270;
	std::vector<std::string> i550;
	std::vector<std::string> i310;
	std::vector<std::string> i500;
	std::vector<std::string> i280;
	std::vector<std::string> i131;
	std::vector<std::string> i210;
}itemset;

std::vector<std::string> Asterix10_parser::Hextobin(std::vector<std::string> results) {
	int jbyte = results.size();
	std::vector<std::string> paketbyte;
	std::string hexo, hexoold, hexocon, bytecon, byteoold, byteo;
	for (int j = 0; j < jbyte; j++) {
		std::string hex = results[j];
		for (int i = 0; i <= 1; i++) {
			switch (hex[i])
			{
			case '0':
				hexo = "0000";
				break;
			case '1':
				hexo = "0001";
				break;
			case '2':
				hexo = "0010";
				break;
			case '3':
				hexo = "0011";
				break;
			case '4':
				hexo = "0100";
				break;
			case '5':
				hexo = "0101";
				break;
			case '6':
				hexo = "0110";
				break;
			case '7':
				hexo = "0111";
				break;
			case '8':
				hexo = "1000";
				break;
			case '9':
				hexo = "1001";
				break;
			case 'a':
			case 'A':
				hexo = "1010";
				break;
			case 'b':
			case 'B':
				hexo = "1011";
				break;
			case 'C':
			case 'c':
				hexo = "1100";
				break;
			case 'd':
			case 'D':
				hexo = "1101";
				break;
			case 'e':
			case 'E':
				hexo = "1110";
				break;
			case 'f':
			case 'F':
				hexo = "1111";
				break;
			}
			hexocon = hexoold + hexo;
			hexoold = hexo;
		}
		paketbyte.push_back(hexocon);
	}
	return paketbyte;
}

std::string vectostring(std::vector<std::string> paket)
{
	std::string paketstring = "";
	int n = paket.size();
	for (int i = 0; i < n; i++)
	{
		paketstring = paketstring + paket[i];
	}
	std::cout << paketstring << std::endl;
	return paketstring;
}

void Asterix10_parser::divide_vector(struct partial_asterix* asterix, int start, int stop)
{
	std::vector<std::string> vector_take, vector_remain;
	std::vector<std::string> paketbit = asterix->asterix_remain;
	for (int i = start; i <= stop; i++) {
		vector_take.push_back(paketbit[i]);
	}
	for (int i = stop + 1; i < paketbit.size(); i++) {
		vector_remain.push_back(paketbit[i]);
	}
	asterix->asterix_remain = vector_remain;
	asterix->asterix_take = vector_take;
}


std::string Asterix10_parser::Fspec(struct partial_asterix* paketbitv) {
	std::string fspec, fspec1 = "", fspec2 = "", fspec3 = "", fspec4 = "";
	fspec1 = paketbitv->asterix_remain[0];
	if (fspec1[7] == '1') {
		fspec2 = paketbitv->asterix_remain[1];
		if (fspec2[7] == '1') {
			fspec3 = paketbitv->asterix_remain[2];
			if (fspec3[7] == '1') {
				fspec4 = paketbitv->asterix_remain[3];
			}
		}
	}
	fspec = fspec1 + fspec2 + fspec3 + fspec4;
	int fspec_size = fspec.length() / 8;
	divide_vector(paketbitv, 0, fspec_size - 1);
	return fspec;
}

void Asterix10_parser::sequence(std::string tes)
{
	std::string hasil = tes, fspec;
	std::vector<std::string> pakethex, paketbitv, cat, len;
	boost::split(pakethex, hasil, [](char c) {return c == ','; });
	struct partial_asterix paketvar;
	struct partial_asterix* paket;
	paket = new struct partial_asterix;
	if (paket == NULL) exit(1);
	paket = &paketvar;
	paket->asterix_remain = Hextobin(pakethex);
	vectostring(paket->asterix_remain);
	//std::cout << paket->asterix_remain[0] << std::endl;
	divide_vector(paket, 0, 0);
	cat = paket->asterix_take;
	//std::cout << cat[0] << std::endl;
	divide_vector(paket, 0, 1);
	len = paket->asterix_take;
	std::cout << "len" << std::stoi(len[0]+len[1],nullptr,2) << std::endl;
	fspec = Fspec(paket);
	std::cout << "FSPEC : " << fspec << std::endl;
	I010(fspec, paket);
	I000(fspec, paket);
	I020(fspec, paket);
	I140(fspec, paket);
	I041(fspec, paket);
	I040(fspec, paket);
	I042(fspec, paket);
	if (fspec[7] == '1')
	{
		I200(fspec, paket);
		I202(fspec, paket);
		I161(fspec, paket);
		I170(fspec, paket);
		I060(fspec, paket);
		I220(fspec, paket);
		I245(fspec, paket);
		if (fspec[15] == '1')
		{
			I250(fspec, paket);
			I300(fspec, paket);
			I090(fspec, paket);
			I091(fspec, paket);
			I270(fspec, paket);
			I550(fspec, paket);
			I310(fspec, paket);

			if (fspec[23] == '1')
			{
				I500(fspec, paket);
				I280(fspec, paket);
				I131(fspec, paket);
				I210(fspec, paket);
			}
		}
	}
}

void Asterix10_parser::I010(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[0] == '1')
	{
		divide_vector(paket, 0, 1);
		itemset.i010 = paket->asterix_take;
		std::cout << "i010 : ";
		vectostring(itemset.i010);
	}
}

void Asterix10_parser::I000(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[1] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i000 = paket->asterix_take;
		std::cout << "i000 : ";
		vectostring(itemset.i000);
	}
}

void Asterix10_parser::I020(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[2] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i020 = paket->asterix_take;
		if (itemset.i020[0][7] == '1')
		{
			divide_vector(paket, 0, 0);
			itemset.i020.push_back(paket->asterix_take[0]);
			if (itemset.i020[1][7] == '1')
			{
				divide_vector(paket, 0, 0);
				itemset.i020.push_back(paket->asterix_take[0]);
			}
		}
		std::cout << "i020 : ";
		vectostring(itemset.i020);
	}
}

void Asterix10_parser::I140(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[3] == '1')
	{
		divide_vector(paket, 0, 2);
		itemset.i140 = paket->asterix_take;
		std::cout << "i140 : ";
		vectostring(itemset.i140);
	}

}

void Asterix10_parser::I041(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[4] == '1')
	{
		divide_vector(paket, 0, 7);
		itemset.i041 = paket->asterix_take;
		std::cout << "i041 : ";
		vectostring(itemset.i041);
	}

}

void Asterix10_parser::I040(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[5] == '1')
	{
		divide_vector(paket, 0, 3);
		itemset.i040 = paket->asterix_take;
		std::cout << "i040 : ";
		vectostring(itemset.i040);
	}
}

void Asterix10_parser::I042(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[6] == '1')
	{
		divide_vector(paket, 0, 3);
		itemset.i042 = paket->asterix_take;
		std::cout << "i042 : ";
		vectostring(itemset.i042);
	}
}

void Asterix10_parser::I200(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[8] == '1')
	{
		divide_vector(paket, 0, 3);
		itemset.i200 = paket->asterix_take;
		std::cout << "i200 : ";
		vectostring(itemset.i200);
	}
}

void Asterix10_parser::I202(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[9] == '1')
	{
		divide_vector(paket, 0, 3);
		itemset.i202 = paket->asterix_take;
		std::cout << "i202 : ";
		vectostring(itemset.i202);
	}
}

void Asterix10_parser::I161(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[10] == '1')
	{
		divide_vector(paket, 0, 1);
		itemset.i161 = paket->asterix_take;
		std::cout << "i161 : ";
		vectostring(itemset.i161);
	}
}

void Asterix10_parser::I170(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[11] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i170 = paket->asterix_take;
		if (itemset.i170[0][7] == '1')
		{
			divide_vector(paket, 0, 0);
			itemset.i170.push_back(paket->asterix_take[0]);
			if (itemset.i170[1][7] == '1')
			{
				divide_vector(paket, 0, 0);
				itemset.i170.push_back(paket->asterix_take[0]);
			}
		}
		std::cout << "i170 : ";
		vectostring(itemset.i170);
	}
}

void Asterix10_parser::I060(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[12] == '1')
	{
		divide_vector(paket, 0, 1);
		itemset.i060 = paket->asterix_take;
		std::cout << "i060 : ";
		vectostring(itemset.i060);
	}
}

void Asterix10_parser::I220(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[13] == '1')
	{
		divide_vector(paket, 0, 2);
		itemset.i220 = paket->asterix_take;
		std::cout << "i220 : ";
		vectostring(itemset.i220);
	}
}

void Asterix10_parser::I245(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[14] == '1')
	{
		divide_vector(paket, 0, 6);
		itemset.i245 = paket->asterix_take;
		std::cout << "i245 : ";
		vectostring(itemset.i245);
	}
}

void Asterix10_parser::I250(std::string fspec, struct partial_asterix* paket)
{
	int multiply;
	if (fspec[16] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i250 = paket->asterix_take;
		multiply = stoi(itemset.i250[0]) * 8;
		divide_vector(paket, 0, multiply - 1);
		std::cout << "i250 : ";
		vectostring(itemset.i250);
	}
}

void Asterix10_parser::I300(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[17] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i300 = paket->asterix_take;
		std::cout << "i300 : ";
		vectostring(itemset.i300);
	}
}

void Asterix10_parser::I090(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[18] == '1')
	{
		divide_vector(paket, 0, 1);
		itemset.i090 = paket->asterix_take;
		std::cout << "i090 : ";
		vectostring(itemset.i090);
	}
}

void Asterix10_parser::I091(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[19] == '1')
	{
		divide_vector(paket, 0, 1);
		std::cout << "i091 : ";
		itemset.i091 = paket->asterix_take;
	}
	vectostring(itemset.i091);
}

void Asterix10_parser::I270(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[20] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i270 = paket->asterix_take;
		if (itemset.i270[0][7] == '1')
		{
			divide_vector(paket, 0, 0);
			itemset.i270.push_back(paket->asterix_take[0]);
			if (itemset.i270[1][7] == '1')
			{
				divide_vector(paket, 0, 0);
				itemset.i270.push_back(paket->asterix_take[0]);
			}
		}
		std::cout << "i270 : ";
		vectostring(itemset.i270);
	}
}


void Asterix10_parser::I550(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[21] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i550 = paket->asterix_take;
		std::cout << "i550 : ";
		vectostring(itemset.i550);
	}

}

void Asterix10_parser::I310(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[22] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i310 = paket->asterix_take;
		std::cout << "i310 : ";
		vectostring(itemset.i310);
	}
}

void Asterix10_parser::I500(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[24] == '1')
	{
		divide_vector(paket, 0, 3);
		itemset.i500 = paket->asterix_take;
		std::cout << "i500 : ";
		vectostring(itemset.i500);
	}
}

void Asterix10_parser::I280(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[25] == '1')
	{
		int multiply;
		divide_vector(paket, 0, 0);
		itemset.i280 = paket->asterix_take;
		multiply = stoi(itemset.i280[0]) * 2;
		divide_vector(paket, 0, (multiply - 1));
		std::cout << "i280 : ";
		vectostring(itemset.i280);
	}
}

void Asterix10_parser::I131(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[26] == '1')
	{
		divide_vector(paket, 0, 0);
		itemset.i131 = paket->asterix_take;
		std::cout << "i131 : ";
		vectostring(itemset.i131);
	}
}

void Asterix10_parser::I210(std::string fspec, struct partial_asterix* paket)
{
	if (fspec[27] == '1')
	{
		divide_vector(paket, 0, 1);
		itemset.i210 = paket->asterix_take;
		std::cout << "i210 : ";
		vectostring(itemset.i210);
	}
}

std::string Asterix10_decoder::take_sequence(std::string bit_series, int start, int stop) {
	std::string used_bit = "";
	int j = 0;
	for (int i=start;i<=stop;i++){	
		used_bit = used_bit + bit_series[i];
		j++;
	}
	return used_bit;
}

void Asterix10_decoder::I020(struct data_item itemset) {
	std::string item_020 = vectostring(itemset.i020);
	std::string item_020_1, item_020_2, item_020_3, sensor_type, mlat_rply_status, vehicle_type, report_source;
	item_020_1 = take_sequence(item_020, 0, 7);
	int sensor_type_bit = stoi(take_sequence(item_020_1, 5, 7));
	switch (sensor_type_bit)
	{
	case 0:
		sensor_type = "SSR multilateration";
	case 1:
		sensor_type = "Mode S multilateration";
	case 2:
		sensor_type = "ADS-B";
	case 3:
		sensor_type = "PSR";
	case 4:
		sensor_type = "Magnetic Loop System";
	case 5:
		sensor_type = "HF multilateration";
	case 6:
		sensor_type = "Not defined";
	case 7:
		sensor_type = "Other types";
	default:
		break;
	}
	std::cout << sensor_type << std::endl;

	int mlat_rply_status_bit = stoi(take_sequence(item_020_1, 1, 1));
	switch (mlat_rply_status_bit)
	{
	case 1:
		mlat_rply_status = "Corrupted";
	case 0:
		mlat_rply_status = "Not corrupted";
	}
	if (item_020_2[0] == 1) {
		item_020_3 = take_sequence(item_020, 16, 23);
		int report_source_bit = std::stoi(take_sequence(item_020_2, 5, 5));
		switch (report_source_bit) {
		case 1:
			report_source = "Report from target transponder";
		case 0:
			report_source = "Report from fixed transponder";
		}

	if (item_020_1[0] == 1) {
		item_020_2 = take_sequence(item_020, 8, 15);
			int vehicle_type_bit = stoi(take_sequence(item_020_2, 1, 2));
			switch (vehicle_type_bit) {
			case 0:
				vehicle_type = "Undetermined";
			case 1:
				vehicle_type = "Aircraft";
			case 2:
				vehicle_type = "Ground vehicle";
			case 3:
				vehicle_type = "Helicopter";
			}
		}
	}
	std::cout << "Tipe sensor : ";
	std::cout << sensor_type << std::endl;
	std::cout << "Corrupt status : ";
	std::cout << mlat_rply_status << std::endl;
	std::cout << "Transponder source : ";
	std::cout << report_source << std::endl;
	std::cout << "Vehicle type : ";
	std::cout << vehicle_type << std::endl;
}

void Asterix10_decoder::I010(struct data_item itemset) {
	std::string sic = vectostring(itemset.i010);
	std::cout << "SIC : ";
	std::cout << sic << std::endl;
}

void Asterix10_decoder::I140(struct data_item itemset) {
	std::string i140int =  vectostring(itemset.i140);
	int mul_timestamp = std::stoi(i140int,nullptr,2);
	double timestamp = (mul_timestamp * 1) / 128;
	std::cout << "timestamp : ";
	std::cout << timestamp << std::endl;
}
int main() {
	Asterix10_parser ins1;
	Asterix10_decoder ins1d;
	std::string tes = "0a,00,14,d0,00,03,02,1c,57,37,d1,01,04,00,03,03,1c,57,37,00";
		//"0a,00,27,ff,01,09,a0,00,04,01,61,00,1c,59,46,fb,a7,2c,52,4b,d9,97,9c,01,72,16,75,01,42,fb,64,51,2f,28,20,15,00,60,90";
		//"0a,00,27,ff,01,09,a0,00,04,01,69,00,1c,57,e2,fb,a6,89,7c,4b,d9,9e,98,00,e0,4d,8d,01,53,fc,e6,3d,59,16,17,12,ff,b2,83";
		//"0a,00,14,d0,00,04,02,1c,57,c0,d1,01,04,00,04,03,1c,57,c0,00";
		//"0a,00,27,ff,01,09,a0,00,03,01,61,00,1c,59,4c,fb,a3,f2,82,4b,d8,cd,be,02,1f,36,2c,ff,63,03,0c,63,33,28,2c,17,00,97,8f";	
	ins1.sequence(tes);
	return 0;
}