// File    : main.cpp
// Author  : XQWang
// Update  : 1.6.2016
// Synopsis: main function for the SAR simulator for website.

#include <iostream>
#include <cstdlib>
#include <fstream>

#include "pathGenerator.h"

using namespace std;

bool calSarByFile( string* cmd );
int main(int argc, char* argv[])
{
	/*string command = "Command.txt";
	ifstream read( command.c_str() );
	if( !read.is_open() ){
		cout << "Command File Not Found !!\n"; return 0;
	}*/

	//string* cmd = new string [5];

   string* cmd = new string [5];
    cmd[0] = argv[5];
   for( int i=1; i<5; i++ )
	  	cmd[i] = argv[i];
	/*
		cmd[0] -- coefficient
		cmd[1] -- piw
		cmd[2] -- buoy
		cmd[3] -- pathCsv
		cmd[4] -- pathGpx
	*/
	//cmd[0] = "Coefficient.log";
	/*string buff;
	read >> buff;
	while( !read.eof() ){
		if     ( buff == "Initial_Point" ){
			read >> buff; buff = "Update_Input/" + buff + ".csv";
			cmd[1] = buff;
		}
		else if( buff == "Buoy_And_Wind" ){
			read >> buff; buff = "Update_Input/" + buff + ".csv";
			cmd[2] = buff;
		}
		else if( buff == "SAR_csv" ){
			read >> buff; buff = "Output/" + buff + ".csv";
			cmd[3] = buff;
		}
		else if( buff == "SAR_gpx" ){
			read >> buff; buff = "Output/" + buff + ".gpx";
			cmd[4] = buff;
		}
		else;
		read >> buff;
	}*/
    int leng = cmd[3].find_last_of("/");
	_absroute = cmd[3].substr(0,leng);
	string leftMargin = "         ";
  /* cout << "\n\n";
   cout << leftMargin << "����������������������������"          <<           "��������������������������" << endl;
   cout << leftMargin << "��          �}�����|�����{�� -- ���u�}�o��          ��" << endl;
   cout << leftMargin << "���w�w�w�w�w�w�w�w�w�w�w�w�w"          <<           "�w�w�w�w�w�w�w�w�w�w�w�w��" << endl;
   cout << leftMargin << "��                                                  ��" << endl;
   cout << leftMargin << "��  �����ѼơG    Coefficient.log                   ��" << endl;
   cout << leftMargin << "��  �_�l�I�y��:   " << setw(34)<<left << cmd[1] << "��" << endl;
   cout << leftMargin << "��  �B�лP����:   " << setw(34)<<left << cmd[2] << "��" << endl;
   cout << leftMargin << "��  ���|(�y��):   " << setw(34)<<left << cmd[3] << "��" << endl;
   cout << leftMargin << "��  ���|(����):   " << setw(34)<<left << cmd[4] << "��" << endl;
   cout << leftMargin << "��                                                  ��" << endl;
   cout << leftMargin << "����������������������������"          <<           "��������������������������" << endl;
   cout << "\n\n";*/
    calSarByFile( cmd );

   delete[] cmd;
   return 0;
}

bool calSarByFile( string* cmd )
{
	/*
		cmd[0] -- coefficient
		cmd[1] -- piw
		cmd[2] -- buoy
		cmd[3] -- pathCsv
		cmd[4] -- pathGpx
	*/
	/*for(int i=0;i<5;i++){
	cout<<i<<":"<<cmd[i]<<endl;}*/

	PathGenerator* solver = new PathGenerator;
	assert( solver->setCoeff( cmd[0] ) );
	assert( solver->setInitialPoint( cmd[1] ) );
	assert( solver->setCurrent( cmd[2] ) );
	assert( solver->setWind( cmd[2] ) );
	assert( solver->setOutCsv( cmd[3] ) );
	assert( solver->setOutGpx( cmd[4] ) );
	assert( solver->calSAR() );
	delete solver;
	return true;
}
