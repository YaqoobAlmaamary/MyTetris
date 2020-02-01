#pragma once
#include <fstream>
#include <string>

class Leaderboard
{
private:
	int score;
	std::string saveFile;

public:

	// constructor
	Leaderboard()
	{
		saveFile = "Save Files/logs.txt";
		score = 0;
	}

	// methods
	void incrementScore()
	{
		score++;
	}

	void saveScore( std::string playerName )
	{
		std::fstream file;
		// open stream
		file.open( saveFile, std::ios::out | std::ios::app );
		if ( !file.is_open() )
			printf( "failed to open file" );
		file << playerName << "\t" << score << "\n";
		
		// close stream
		file.close();
	}

	std::string loadScores()
	{
		// the final result
		std::string scores = "";
		// buffer to hold the line data
		std::string buffer;

		// file to work on
		std::fstream file;
		// open stream
		file.open( saveFile, std::ios::in );

		if ( !file.is_open() )
			return scores;

		// read line from file and store in buffer
		while ( std::getline( file, buffer ) )
		{
			scores = scores + buffer;
		}
		// close stream
		file.close();
		return scores;
	}

	void resetScores()
	{
		// file to work on
		std::fstream file;
		// opening a file stream to load data to
		file.open( saveFile, std::ios::out | std::ios::trunc );
		// close the stream to avoid memory leaks
		file.close();
	}

	void resetCurrentScore() 
	{
		score = 0;
	}

	int getScore()
	{
		return score;
	}

};

