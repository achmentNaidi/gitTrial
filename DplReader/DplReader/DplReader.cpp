
#include <iostream>
#include <fstream>
#include<string>
#include <vector>
#include <iomanip>



using namespace std;

int main()
{
	vector<int> triangle, quadrature, logfr;
	vector<double> x, y;
	int quads, nodes, triangles, id, nboundaries, counter,nodi;
    string inFile, outFile1, outFile2, alpha;

	inFile= "hybrid.dpl";
	outFile1 = "hybrid.ele";
	outFile2 = "hybrid.nod";
	ifstream dplFile(inFile);
	ofstream eleFile(outFile1), nodFile(outFile2);
	getline(dplFile, alpha);


	if (dplFile.is_open()) //if the file is open
	{
		// Write .ele file
		dplFile >> nodes >> triangles >> quads;
		eleFile << triangles <<" " << quads<<endl;
		triangle.resize(3);
		quadrature.resize(4);

		for (int i = 0; i < triangles; i++)
		{
			dplFile >> id >> triangle[0] >> triangle[1] >> triangle[2];
			eleFile << triangle[0] << " " << triangle[1] << " " << triangle[2] << endl;
			getline(dplFile, alpha);
		}

		for (int i = 0; i < quads; i++)
		{
			dplFile >> id >> quadrature[0] >> quadrature[1] >> quadrature[2] >> quadrature[3];
			eleFile << quadrature[0] << " " << quadrature[1] << " " << quadrature[2] << " " << quadrature[3] << endl;
			getline(dplFile, alpha);
		}
		
		// Write .nod file

		x.resize(nodes);
		y.resize(nodes);

		for (int i = 0; i < nodes; i++)
		{
			dplFile >> x[i] >> y[i];
		}

		dplFile >> nboundaries;
		logfr.resize(nodes);

		counter = 0;

		while (counter < nboundaries) {
			dplFile >> nodi;
			getline(dplFile, alpha);

			for (int i = 0; i < nodes; i++)
			{
				dplFile >> id;
				getline(dplFile, alpha);
				logfr[id - 1] = 3;

			}
			counter++;
		}


		nodFile << nodes << endl;

		for (int i = 0; i < logfr.size(); i++)
		{
			nodFile << logfr[i] << endl;

		}

		for (int i = 0; i < nodes; i++)
		{
			nodFile <<setprecision(9)<< x[i] << endl;
		}

		for (int i = 0; i < nodes; i++)
		{
			nodFile << setprecision(9) << y[i] << endl;
		}

	}
	else {
		cout << "Unable to open file"; //if the file is not open output
	}

	dplFile.close();
	eleFile.close();
	nodFile.close();

	return 0;

}

