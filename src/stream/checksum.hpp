
#ifndef INNOEXTRACT_STREAM_CHECKSUM_HPP
#define INNOEXTRACT_STREAM_CHECKSUM_HPP

#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/read.hpp>

#include "crypto/hasher.hpp"

namespace stream {

class checksum_filter : public boost::iostreams::multichar_input_filter {
	
private:
	
	typedef boost::iostreams::multichar_input_filter base_type;
	
public:
	
	typedef base_type::char_type char_type;
	typedef base_type::category category;
	
	inline checksum_filter(crypto::hasher * _hasher) : hasher(_hasher) { }
	inline checksum_filter(const checksum_filter & o) : hasher(o.hasher) { }
	
	template<typename Source>
	std::streamsize read(Source & src, char * dest, std::streamsize n) {
		
		std::streamsize nread = boost::iostreams::read(src, dest, n);
		
		if(nread != EOF) {
			hasher->update(dest, size_t(nread));
		}
		
		return nread;
	}
	
private:
	
	crypto::hasher * hasher;
	
};

} // namespace stream

#endif // INNOEXTRACT_STREAM_CHECKSUM_HPP