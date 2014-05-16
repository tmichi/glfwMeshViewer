/**
* @file Mesh.hpp
* @brief
*/
#pragma once
#ifndef MESH_HPP
#define MESH_HPP 1
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <deque>
#include <map>
#include <cmath>
#include <Eigen/Dense>
#include "Tokenizer.hpp"
class Mesh
{
	Mesh( const Mesh& that );
	void operator = ( const Mesh& that );
private:
	std::string _name;
	std::vector<Eigen::Vector3d> _vertex; /// vertex position
	std::vector<int> _index; /// triangles
public:
	explicit Mesh ( void )
	{
		this->init();
		return;
	}

	virtual ~Mesh ( void )
	{
		this->_vertex.clear();
		this->_index.clear();
		return;
	}

	int addPoint( Eigen::Vector3d& p )
	{
		this->_vertex.push_back( p );
		return static_cast<int>( this->_vertex.size() - 1 );
	}

	int addFace ( const std::vector<int>& fidx )
	{
		if ( fidx.size() != 3 ) return -1;
		this->_index.insert ( this->_index.end(), fidx.begin(), fidx.end() );
		return static_cast<int>( this->_index.size() / 3 ) ; // ID
	}

	void addName ( const std::string name = std::string( "mesh" ) )
	{
		this->_name = name;
		return;
	}

	inline bool isValidFaceId( const int faceid ) const
	{
		return ( 0 <= faceid && faceid < this->getNumFaces() );
	}

	inline bool isValidVertexId( const int vertexid ) const
	{
		return ( 0 <= vertexid && vertexid < this->getNumVertices() );
	}

	inline std::vector<int> getFaceIndices ( const int faceid ) const
	{
		std::vector<int> idx ( 3, -1 );
		if ( this->isValidFaceId( faceid ) ) {
			for ( int i = 0 ; i < 3 ; i++ ) {
				idx[i] = this->_index.at ( faceid * 3 + i );
			}
		}
		return idx;
	}

	inline Eigen::Vector3d getPosition ( const int vertexid ) const
	{
		if ( this->isValidVertexId( vertexid ) ) return this->_vertex.at ( vertexid );
		return Eigen::Vector3d();
	}


	Eigen::Vector3d getNormal ( const int faceid , bool normalize = true ) const
	{
		if ( ! this->isValidFaceId( faceid ) ) return Eigen::Vector3d();

		std::vector<int> fidx = this->getFaceIndices( faceid );
		Eigen::Vector3d v0 = this->getPosition( fidx[0] );
		Eigen::Vector3d v1 = this->getPosition( fidx[1] ) - v0;
		Eigen::Vector3d v2 = this->getPosition( fidx[2] ) - v0;
		Eigen::Vector3d n = v1.cross( v2 );

		if ( normalize ) n.normalize();
		return n;
	}

	inline std::string
		getName ( void ) const
	{
		return this->_name;
	}


	void setPosition ( const int vertexid, const Eigen::Vector3d& pos )
	{
		if ( this->isValidVertexId( vertexid ) ) {
			this->_vertex.at ( vertexid ) = pos;
		}
		return;
	};
	void init( void )
	{
		this->_vertex.clear();
		this->_index.clear();
		return;
	}

	inline int getNumVertices( void ) const
	{
		return static_cast<int>( this->_vertex.size() );
	}

	inline int getNumFaces( void ) const
	{
		return static_cast<int>( this->_index.size() / 3 );
	}

	void
		getBoundingBox ( Eigen::Vector3d& bmin, Eigen::Vector3d& bmax )
	{
		const size_t numv = this->getNumVertices();
		if ( numv == 0 ) {
			std::cerr<<"No vertices. return nothing."<<std::endl;
			return;
		}
		bmin = this->getPosition ( 0 );
		bmax = this->getPosition ( 0 );
		for ( size_t i = 1 ; i < numv ; ++i ) {
			const Eigen::Vector3d v = this->getPosition ( static_cast<int>( i ) );
			if ( v.x() < bmin.x() ) bmin.x() = v.x();
			if ( v.y() < bmin.y() ) bmin.y() = v.y();
			if ( v.z() < bmin.z() ) bmin.z() = v.z();

			if ( v.x() > bmax.x() ) bmax.x() = v.x();
			if ( v.y() > bmax.y() ) bmax.y() = v.y();
			if ( v.z() > bmax.z() ) bmax.z() = v.z();
		}
		return ;
	}

	void negateOrientation()
	{
		for( int i = 0 ; i < this->getNumFaces() ; ++i ) {
			int f0 = this->_index [ i * 3 + 0 ];
			int f1 = this->_index [ i * 3 + 1 ];
			this->_index[ i * 3 + 1 ] = f0;
			this->_index[ i * 3 + 0 ] = f1;
		}

	}


	bool read (const  std::string& filename) {
		std::vector<Eigen::Vector3d> vx;
		std::deque< std::deque< std::deque<int> > > index;
		std::ifstream fin ( filename.c_str() );

		if ( !fin ) {
			std::cerr<<"Open failed."<< filename <<std::endl;
			return false;
		}

		int count = -1
			;
		while ( fin ) {
			std::string  buffer;
			std::getline( fin, buffer );
			if( fin.eof() ) break;
			if ( buffer.find_first_of( "#" ) == 0 ) continue;
			if ( buffer.length() == 0 ) continue;

			Tokenizer tokenizer1 ( buffer, " " ) ;
			if ( tokenizer1.size() == 0 ) continue;
			if ( tokenizer1.get( 0 ).compare( "v" ) == 0 ) {
				Eigen::Vector3d p;
				p.x() = std::atof( tokenizer1.get( 1 ).c_str() );
				p.y() = std::atof( tokenizer1.get( 2 ).c_str() );
				p.z() = std::atof( tokenizer1.get( 3 ).c_str() );
				vx.push_back( p );
			}
			if ( tokenizer1.get( 0 ).compare( "g" ) == 0 ) {
				count++;
				index.push_back( std::deque<std::deque<int> > () );
			}
			if ( tokenizer1.get( 0 ).compare( "f" ) == 0 ) {
				if ( count == -1 ) {
					count++;
					index.push_back( std::deque<std::deque<int> > () );
				}
				index[count].push_back( std::deque<int> () );
				for( int i = 1 ; i < tokenizer1.size() ; ++i ) {
					Tokenizer tokenizer2( tokenizer1.get( i ), "/" );
					if ( tokenizer2.get(0).length() != 0 ) {
						int fid =  std::atoi( tokenizer2.get( 0 ).c_str() );
						if( fid != 0) index[count][index[count].size() - 1].push_back(fid - 1 );
					}
				}
			}
		}
		std::cerr<<"ok"<<std::endl;

		this->init();
		for ( size_t i = 0 ; i < vx.size() ; ++i ) {
			this->addPoint( vx[i] );
		}
		for( size_t i = 0 ; i < index.size() ; ++i ) {
			for( size_t j = 0 ; j < index[i].size() ; ++j ) {
				//“K“–‚ÈŽÀ‘•
				for ( size_t k = 0  ; k < index[i][j].size() - 2; ++k ) {
					std::vector<int> fid;
					fid.push_back( index[i][j][0] );
					fid.push_back( index[i][j][k+1] );
					fid.push_back( index[i][j][k+2] );
					this->addFace( fid );
				}
			}
		}
		std::cerr<<"done"<<std::endl;

		return true;
	}
};
#endif
