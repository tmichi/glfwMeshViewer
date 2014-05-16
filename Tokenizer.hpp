/**
 * @file Tokenizer.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#pragma once
#ifndef MI_TOKENIZER_HPP
#define MI_TOKENIZER_HPP 1
#include <string>
#include <vector>
#include <iostream>

/**
 * @class Tokenizer Tokenizer.hpp "mi/Tokenizer.hpp"
 * @brief Tokenize the string.
 */
class Tokenizer
{
private:
        Tokenizer ( const Tokenizer& that ) ;
        void operator = ( const Tokenizer& that ) ;
public:
        /**
         * @brief Constructor.
         * @param [in] str String.
         * @param [in] delimiter Delimiter of the string.
         */
        explicit Tokenizer ( const std::string& str, const std::string delimiter = std::string ( " " ) )
        {
                std::string::size_type end;
                std::string line = str;

                for ( ; ; ) {
                        end = line.find_first_of ( delimiter );
                        if ( line.substr ( 0, end ).length() > 0 ) {
                                this->_token.push_back ( line.substr ( 0, end ) );
                        }
                        if ( std::string::npos == end ) break;
                        line = line.substr ( end + 1 );
                }
                return;
        };
        /**
         * @brief Destructor.
         */
        ~Tokenizer ( void )
        {
                return;
        }

        /**
         * @brief Get the number of tokens.
         * @return The number of tokens.
         */
        int size ( void ) const
        {
                return static_cast<int>( this->_token.size() );
        }

        /**
         * @brief Get a token.
         * @param [in] i Index.
         * @return Token.
         */
        std::string get ( const int i ) const
        {
                return this->_token.at( i );
        }

        /**
         * @brief Print all tokens.
         */
        void printAll ( void )
        {
                std::cout<<"Num. of Tokens : "<<this->size()<<std::endl;
                for( int i = 0 ; i < this->size() ; ++i ) {
                        std::cout<<"token["<<i<<"] : "<<this->get( i )<<std::endl;
                }
                return;
        }
private:
        std::vector<std::string> _token; ///<Tokens
};

#endif//MI_TOKENIZER_HPP
