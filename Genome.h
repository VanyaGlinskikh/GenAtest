/*
 * Genome.h
 *
 *  Created on: 2 мар. 2021 г.
 *      Author: vanya
 */

#ifndef GENOME_H_
#define GENOME_H_

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>

class Genome
{
public:
	using data_type = int32_t;
	using section_type = std::vector<data_type>;
	using genome_structure_type = std::vector<section_type>;
protected:
	genome_structure_type _data {};
public:
	Genome() {}
	Genome(const Genome& g);

	void add_section(const section_type & section_data)
	{
		_data.push_back({});
		_data.back().resize(section_data.size());
		std::copy(section_data.begin(), section_data.end(), _data.back().begin());
	}

	genome_structure_type::size_type sections() const { return _data.size(); }
	section_type::size_type section_size(unsigned section) const
	{
		if (section >= _data.size())
			throw std::out_of_range("Invalid section number");
		return _data[section].size();
	}
	data_type& operator ()(unsigned section, unsigned location)
	{
		if (location >= section_size(section)) // may throw an OOR exception
			throw std::out_of_range("Invalid location");
		return _data[section][location];
	}

	void mutate(unsigned section, unsigned location, unsigned bit);

	friend Genome splice(const Genome& g1, const Genome& g2, const std::vector<uint8_t> & order);
};



#endif /* GENOME_H_ */
