#ifndef KENOBET_H
#define KENOBET_H

#include <vector>
#include <algorithm>

using number_type = unsigned short int;
using cash_type = float;
using set_of_numbers_type = std::vector< number_type >;

class KenoBet 
{
public:

	/**
	 * @brief      Constructs the object.
	 */
	KenoBet() : m_wage(0){};

	/**
	 * @brief      Adds a number to the spots only if the number is not already there.
	 *
	 * @param[in]  spot_  The number we wish to include in the bet.
	 *
	 * @return     True if number chosen is successfully inserted; false otherwise.
	 */
	bool add_number( number_type spot_ );

	/**
	 * @brief      Sets the amount of money the player is betting.
	 *
	 * @param[in]  wage_  The wage
	 *
	 * @return     True if we have a wage above zero; false otherwise.
	 */
	bool set_wage( cash_type wage_ );

	/**
	 * @brief      Resets a bet to an empty state
	 */
	void reset( void ) ;

	/**
	 * @brief      Retrieves the player's wage on this bet.
	 *
	 * @return     The wage value.
	 */
	cash_type get_wage( void ) const;

	/**
	 * @brief      Returns to the current number of spots in the player's bet.
	 *
	 * @return     Number of spots present in the bet.
	 */
	size_t size ( void ) const;

	/**
	 * @brief      Determine how many spots match the hits passed as argument.
	 *
	 * @param[in]  hits_  List of hits randomly chosen by the computer.
	 *
	 * @return     An vector with the list of hits.
	 */
	set_of_numbers_type get_hits( const set_of_numbers_type & hits_ ) const;

	/**
	 * @brief      Return a vector < spot_type > with the spots the player has picked so far.
	 *
	 * @return     The vector < spot_type > with the player ’s spots picked so far.
	 */
	set_of_numbers_type get_spots( void ) const;

private:
	set_of_numbers_type m_spots;
	cash_type m_wage;
};

#endif