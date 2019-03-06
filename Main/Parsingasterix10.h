#include<stdio.h>
#include<stdlib.h>
#include <boost/algorithm/string.hpp>
#include<iostream>
#include <vector>
#include <string>

#ifndef PARSEASTERIX_H
#define PARSEASTERIX_H

std::string vectostring(std::vector<std::string> paket);

class Asterix10_parser {
private:
	std::string Fspec(std::vector<std::string> *paketbitv);
	std::vector<std::string> Hextobin(std::vector<std::string> results);
	void I010(std::string fspec, struct partial_asterix* paket);
	void I000(std::string fspec, struct partial_asterix* paket);
	void I020(std::string fspec, struct partial_asterix* paket);
	void I140(std::string fspec, struct partial_asterix* paket);
	void I041(std::string fspec, struct partial_asterix* paket);
	void I040(std::string fspec, struct partial_asterix* paket);
	void I042(std::string fspec, struct partial_asterix* paket);
	void I200(std::string fspec, struct partial_asterix* paket);
	void I202(std::string fspec, struct partial_asterix* paket);
	void I161(std::string fspec, struct partial_asterix* paket);
	void I170(std::string fspec, struct partial_asterix* paket);
	void I060(std::string fspec, struct partial_asterix* paket);
	void I220(std::string fspec, struct partial_asterix* paket);
	void I245(std::string fspec, struct partial_asterix* paket);
	void I250(std::string fspec, struct partial_asterix* paket);
	void I300(std::string fspec, struct partial_asterix* paket);
	void I090(std::string fspec, struct partial_asterix* paket);
	void I091(std::string fspec, struct partial_asterix* paket);
	void I270(std::string fspec, struct partial_asterix* paket);
	void I550(std::string fspec, struct partial_asterix* paket);
	void I310(std::string fspec, struct partial_asterix* paket);
	void I500(std::string fspec, struct partial_asterix* paket);
	void I280(std::string fspec, struct partial_asterix* paket);
	void I131(std::string fspec, struct partial_asterix* paket);
	void I210(std::string fspec, struct partial_asterix* paket);

	std::string Fspec(struct partial_asterix* paketbitv);
	

	void divide_vector(struct partial_asterix* asterix, int start, int stop);
public:
	void sequence(std::string tes);
};

class Asterix10_decoder {
public:
	struct decode_item {
		std::string tipe_sensor;
	};

	std::string take_sequence(std::string bit_series, int start, int stop);
	void I010(struct data_item itemset);
	void I020(struct data_item itemset);
	void I140(struct data_item itemset);
};

#endif // !PARSEASTERIX_H