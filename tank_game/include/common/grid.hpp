#pragma once

#include <vector>
#include <iterator>

template <typename T>
class Grid {
    /**
     *	A simple 2D container
     **/

	protected:
		size_t m_Nlines;
		size_t m_Ncols;
		std::vector<T> m_data;

	public:

		Grid(const size_t n, const size_t m, const T& default_value = T())
		:
			m_Nlines(n),
			m_Ncols(m)
		{
			m_data = std::vector<T>(n*m, default_value);
		}

		const size_t nb_lines() const {
			return m_Nlines;
		}

		const size_t nb_cols() const {
			return m_Ncols;
		}

		const T& operator()(const size_t i, const size_t j) const {
			return m_data[i*m_Ncols + j];
		}

		T& operator()(const size_t i, const size_t j) {
			return m_data[i*m_Ncols + j];
		}
		
		void fill(const T& val = T()) {
			for (size_t i = 0 ; i < m_data.size() ; ++i) {
				m_data[i] = val;
			}
		}

		void clear(){ fill(); }

		typename std::vector<T>::iterator begin() { return m_data.begin();}
        typename std::vector<T>::iterator end() { return m_data.end();}

	};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Grid<T>& v) {
	os << std::endl;
	for (size_t i = 0 ; i < v.nb_lines() ; ++i) {
		for (size_t j = 0 ; j < v.nb_cols() ; ++j) {
			os << v(i,j) << " ";
		}
		os << "\n";
	}
    return os;
}