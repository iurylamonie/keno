#include "kenobet.h"

bool KenoBet::add_number( number_type spot_ )
{
	if( spot_ >= 1 and spot_ <= 80)
	{
		if( m_spots.size() ) ///< Verifica se já foi salvo algum spot do jogador.
		{	
			auto rbsearch = std::binary_search( m_spots.begin(), m_spots.end(), spot_ );

			if( !rbsearch ) ///< Caso o spot não exista em m_spots, ele é inserido.
			{
				m_spots.push_back( spot_ );
				std::sort( m_spots.begin(), m_spots.end() );
				return true;
			}
		}
		else { m_spots.push_back( spot_ ); return true; } ///< Caso nenhum spot tenha sido salvo ainda
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
	set_of_numbers_type rhits;///< Armazena em ordem crescente os acertos do jogador
	for( auto i : hits_ )
	{
		auto rbsearch = std::binary_search( m_spots.begin(), m_spots.end(), i);
		if( rbsearch ) rhits.push_back( i );
	}

	return rhits;
}

set_of_numbers_type KenoBet::get_spots( void ) const { return m_spots; }
