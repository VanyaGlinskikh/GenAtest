/*
 * Genome.cc
 *
 *  Created on: 2 мар. 2021 г.
 *      Author: vanya
 */
#include "Genome.h"
#include <iostream>
Genome::Genome(const Genome& g)
{
	_data.resize(g.sections());
	for (unsigned i = 0; i < g.sections(); ++i) {
		_data[i].resize(g._data[i].size());
		std::copy(g._data[i].begin(), g._data[i].end(), _data[i].begin());
	}
}


void Genome::mutate(unsigned section, unsigned location, unsigned bit)
{
	if (location >= section_size(section)) // may throw an OOR exception
		throw std::out_of_range("Invalid location");

	if (bit >= sizeof(data_type))
		throw std::runtime_error("Invalid bit index");
	_data[section][location] ^= (1 << bit);
}

Genome splice(const Genome& g1, const Genome& g2, const std::vector<uint8_t> & order)
{
	Genome result;
	if (g1.sections() != g2.sections())
		throw std::runtime_error("Genome sizes don't match!");
	if (order.size() < g1.sections())
		throw std::runtime_error("Not enough data for splicing!");

	for (unsigned i = 0; i < g1.sections(); ++i)
		if ((order[i] & 1) == 0)
			result.add_section(g1._data[i]);
		else
			result.add_section(g2._data[i]);

	return result;
}



