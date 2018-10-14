#include <iostream>
#include <fstream> // fstream
#include <cstdlib> // exit()
#include <string> // string
#include <random>

#include "kenobet.h"

int main(int argc, char const *argv[])
{
	if(argc > 1)
	{	
		double tabela_preco[15][16]; ///< Armazena a "payout table"; carregada do arquivo doc/payout.doc
		std::ifstream filepay("doc/payout.dat");
		if( filepay.is_open() )
		{
			std::string strImput;
			int i = 0, j = 0;
			while(filepay >> strImput) ///< O operador de extração "ignora" os espaços em branco
			{
				tabela_preco[i][j] = std::stod(strImput);
				if( ++j == 16 )
				{
					++i;
					j = 0;
				}
			}
		} else std::cout << ">>> doc/payout.dat was not foud!" << std::endl; 
		filepay.close();
		
		///Carregando o arquivo bets.
		std::ifstream ifile( *(argv + 1) );
		if( ifile.is_open() )
		{
			std::cout << ">>> Preparing to read bet file " << *(argv + 1) << ", please wait..." << std::endl;			
			std::cout << "--------------------------------------------------" << std::endl;	

			KenoBet kb;
			cash_type ic, ///< initial credit 
					net_balance; ///< saldo líquido
			int nr, i = 0; ///< nr = número de rodadas
			std::string strImput;

			///Coleta as informações validas no arquivo bets
			while( ifile >> strImput )
			{
				if( i == 0)
				{
					net_balance = ic = std::stof( strImput );
					++i;
				}
				else if( i == 1)
				{
					nr = std::stoi( strImput );
					kb.set_wage( ic/nr );
					++i;
				}
				else if ( kb.size() < 15 )
				{
					kb.add_number( std::stoi( strImput ) );
				}
				else break;
			}

			///Caso não tenha nenhuma bets ou nr invalido.
			if( kb.size() == 0 or nr < 1 )
			{
				std::cout << ">>> Bet fail read!" << std::endl;
				std::exit(1);
			}

			///==IMPRIMINDO INFORMAÇÕES PARA O JOGADOR
			std::cout << ">>> Bet successfully read!" << std::endl  << std::endl;
			std::cout << "You are going to wage a total of $" << ic << " dollars." << std::endl;
			std::cout << "Going for a total of " << nr << " rounds, waging $" << kb.get_wage() << " per round." << std::endl << std::endl;
			std::cout << "Your bet has " << kb.size() <<" numbers. They are: [ ";
			for( auto num : kb.get_spots() )
			{
				std::cout <<  num << " ";
			}
			std::cout << "]" << std::endl;
			for(int k = 0 ; k <= kb.size() ; ++k)
			{
				std::cout << "Hits: " << k << " - Payout: x" << tabela_preco[kb.size() - 1][k] << std::endl;
			}
			///==FIM DAS INFORMAÇÕES
			

			std::random_device rd; ///< Will be used to obtain a seed for the random number engine.
			std::mt19937 mt(rd()); ///< Standard mersenne_twister_engine seeded with rd().
			std::uniform_int_distribution<int> num_random(1,80);
									
			///Gerenciador de Rodadas
			for(int r = 0; r < nr ; ++r)
			{
				///==INFORMAÇÕES INICIAIS DA RODADA
				std::cout << "--------------------------------------------------" << std::endl;
				std::cout << "This is round #" << r+1 << " of " << nr <<", and your wage is $"
				<< kb.get_wage() << ". Good luck!" << std::endl;
				///==FIM DAS INFORMAÇÕES

				set_of_numbers_type num_sorteados; ///< Armazena os 20 números sorteados
				num_sorteados.push_back( num_random( mt ) );
				set_of_numbers_type hits; ///< Armazena os números que o jogador acertou
				
				///Sorteia os 20 números
				for(int q = 1; q < 20; ++q )
				{	
					while(1)
					{
						int n = num_random(mt);
						auto rbsearch = std::binary_search( num_sorteados.begin(), num_sorteados.end(), n );
						///Verifica se atual número sorteado já foi sorteado anteriormente.
						if( !rbsearch )
						{
							num_sorteados.push_back( n );
							std::sort( num_sorteados.begin(), num_sorteados.end() );
							break;
						}
					} 	
				}

				///Śalva em hits os números que o jogador acertou
				for( auto sort : kb.get_hits( num_sorteados ) )
				{
					hits.push_back( sort );
				}

				///==IMPRIMINDO INFORMAÇÕES
				std::cout << "The hits are: [ ";
				for( auto num : num_sorteados )
				{
					std::cout <<  num << " ";
				}
				std::cout << " ]" << std::endl;
				std::cout << std::endl << std::endl;
				std::cout << "You hit the following number(s) [ ";
				for( auto num : hits )
				{
					std::cout <<  num << " ";
				}
				std::cout << "], a total of " << hits.size() << " hit out of " 
				<< kb.size() << std::endl;
				std::cout << "Payout rate is " << tabela_preco[kb.size() - 1][hits.size()]
				<< ", thus you came out with: $" << kb.get_wage() * tabela_preco[kb.size() - 1][hits.size()]
				<< std::endl;

				///Atualiza o valor do saldo do jogador
				net_balance = (net_balance - kb.get_wage()) + (kb.get_wage() * tabela_preco[kb.size() - 1][hits.size()]);

				std::cout << "Your net balance so far is: $" << net_balance << " dollars." << std::endl;
				///==FIM DAS INFORMAÇÕES
				
				///==="LIMPANDO" OS VECTORS
				num_sorteados.clear();
				hits.clear();								
			}///==FIM DOS ROUNDS

			///==IMPRIMINDO INFORMAÇÕES FINAIS DO JOGO
			std::cout << "\n>>>End of rounds!" << std::endl;
			std::cout << "--------------------------------------------------" << std::endl;
			std::cout << std::endl << std::endl;
			std::cout << "===== SUMMARY =====" << std::endl;
			std::cout << ">>> You spent in this game a total of $" << ic <<" dollars." << std::endl;
			if( net_balance > ic )
				std::cout << ">>> Hooray, you won $" << net_balance - ic <<" dollars. See you next time! ;-)" << std::endl;
			else std::cout << ">>> You lost $" << ic - net_balance <<" dollars. See you next time! ;-)" << std::endl;
			std::cout << ">>> You are leaving the Keno table with $" << net_balance <<" dollars." << std::endl;
			///==FIM DAS INFORMAÇÕES
		}
		else std::cout << ">>> " << *(argv + 1) << " was not foud!" << std::endl;
		ifile.close();
	}
	else std::cout << ">>> Enter the file name!" << std::endl;
	return 0;
}