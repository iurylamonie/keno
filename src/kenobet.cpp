#include <algorithm>

#include "kenobet.h"

bool KenoBet::add_number( number_type spot_ )
{
	if( spot_ >= 1 and spot_ <= 80)
	{
		//Verifica se já foi inserido outros spots.
		if( m_spots.size() )
		{	
			auto rbsearch = std::binary_search( m_spots.begin(), m_spots.end(), spot_ );

			if( !rbsearch )
			{
				m_spots.push_back( spot_ );
				std::sort( m_spots.begin(), m_spots.end() );
				return true;
			}
		}
		else { m_spots.push_back( spot_ ); return true; }
	} 

	return false;
}

bool KenoBet::set_wage( cash_type wage_ )
{ 
	if( wage_ > 0 ) 
	{
		m_wage = wage_;
		return true;
	}
	return false;
}

void KenoBet::reset( void )
{ 
	m_wage = 0;
	m_spots.clear();
}

cash_type KenoBet::get_wage( void ) const { return m_wage; }

size_t KenoBet::size ( void ) const { return m_spots.size(); }

set_of_numbers_type KenoBet::get_hits( const set_of_numbers_type & hits_ ) const
{ 
	set_of_numbers_type rhits;
	std::sort( hits_.begin(), hits_.end() );
	for( auto i : m_spots)
	{
		auto rbsearch = std::binary_search( hits_.begin(), hits_.end(), i);
		if( rbsearch ) rhits.push_back( i );
	}

	return rhits;
}

set_of_numbers_type KenoBet::get_spots( void ) const { return m_spots; }
