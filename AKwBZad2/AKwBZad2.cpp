

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<iterator>
#include<algorithm>
#include <cstdlib>


std::vector<std::vector<int>>tab;
std::vector<std::vector<int>>edges;


int counter = -1;

int One()
{
	int blad;
	for (int g = 0; g < counter; g++)
	{
		for (int h = 1; h < tab[g].size() - 1; h++)
		{
			for (int l = h + 1; l < tab[g].size(); l++)
			{
				if (tab[g][h] == tab[g][l])
				{
					std::cout << "to jest multi graf" << std::endl;
					return 0;
				}

			}
		}
	}
	std::cout << "to jest jeden graf" << std::endl;
	return 1;
}

void transform()
{
	int a = 1, b = 1, c = 2;
	int zmienna1, zmienna2, zmienna3;
	for (int i = 0; i < counter; i++)
	{
		std::vector<int>list;
		list.push_back(a);
		list.push_back(b);
		list.push_back(c);

		edges.push_back(list);

		a++;
		b = b + 2;
		c = c + 2;
	}

	for (int x = 0; x < counter; x++)
		for (int y = 1; y < tab[x].size(); y++)
		{
			zmienna1 = tab[x][y];
			zmienna3 = edges[x][2];
			zmienna2 = edges[zmienna1 - 1][1];
			edges[zmienna1 - 1][1] = zmienna3;

			for (int h = 0; h < counter; h++)
			{
				if (edges[h][1] == zmienna2)
				{
					edges[h][1] = zmienna3;
				}
				if (edges[h][2] == zmienna2)
				{
					edges[h][2] = zmienna3;
				}
			}

		}
	for (int i = 0; i < counter; i++)
	{
		for (int j = 0; j < edges[i].size(); j++)
			std::cout << edges[i][j] << "  ";
		std::cout << std::endl;
	}
	int que = 1;
	for (int j = 0; j < counter; j++)
	{
		for (int n = 1; n < edges[j].size(); n++)
		{
			if (edges[j][n] >= que)
			{
				int schowek = edges[j][n];
				for (int a = 0; a < counter; a++)
				{
					for (int m = 1; m <= 2; m++)
					{
						if (edges[a][m] == schowek)
						{
							edges[a][m] = que;


						}
					}
				}
				que++;
			}
		}
	}
	for (int i = 0; i < counter; i++)
	{
		for (int j = 0; j < edges[i].size(); j++)
			std::cout << edges[i][j] << "  ";
		std::cout << std::endl;
	}
	std::ofstream file;
	std::string file_Name;

	std::cout << std::endl << "Enter the file name: \t" << std::endl;
	std::cin >> file_Name;
	file_Name += ".txt";
	file.open(file_Name.c_str());

	if (file.good() == true)
	{

		for (int i = 1; i < que; i++)
		{
			file << i << " ";

			for (int j = 0; j < counter; j++)
			{
				if (edges[j][1] == i)
				{
					file << edges[j][2] << " ";
				}
			}
			file << "0" << "\n";
		}
	}
	else std::cout << "Error file! " << std::endl;

}

bool checklinia()
{
	int worek1, worek2;

	for (int c = 0; c < counter; c++)
	{
		if (tab[c].size() > 2)
		{
			
			for (int d = 1; d < tab[c].size(); d++)
			{
				for (int k = d + 1; k < tab[c].size(); k++)
				{
					worek1 = tab[c][d];
					worek2 = tab[c][k];
					
					for (int xy = 1; xy < tab[worek1 - 1].size(); xy++)
					{
						for (int zz = 1; zz < tab[worek2 - 1].size(); zz++)
						{
							if (tab[worek1 - 1][xy] == tab[worek2-1][zz])
							{
								std::cout << "to nie jest graf liniowy" << std::endl;
								return false;
							}
						}
					}
				}
			}
		}

		
	}
	std::cout << "to jest graf liniowy" << std::endl;
		return true;
}

int check()
{

	int z1, z2;
	int same = 0;

	for (int i = 0; i < counter; i++)
	{
		for (int j = i + 1; j < counter; j++)
		{

			for (int a = 1; a < tab[i].size(); a++)
			{

				for (int b = 1; b < tab[j].size(); b++)
				{
					if (tab[i][a] == tab[j][b])
					{
						z1 = i;
						z2 = j;
						if (tab[z1].size() == tab[z2].size())
						{
							for (int x = 1; x < tab[z1].size(); x++)
							{
								int blad = tab[z1][x];

								for (int abc = 1; abc < tab[z2].size(); abc++)
								{
									if (blad == tab[z2][abc])
									{
										same = 1;
									}


								}
								if (same == 0)
								{
									std::cout << " to nie jest graf sprzê¿ony"<<std::endl;
									return 0;
								}
							}



						}
						else
						{
							std::cout << "to nie jest graf sprzezony" << std::endl;
							return 0;
						}
					}





				}
			}
		}
	}

	std::cout << "to jest graf sprze¿ony " << std::endl;


	One();
	checklinia();


	transform();

	return 1;
}
int main()
{

	std::fstream plik("nowy.txt", std::ios::in);
	if (plik.is_open())
	{
		int kontener;

		while (!plik.eof())
		{
			plik >> kontener;

			std::vector<int>Htab;
			counter++;

			while (kontener != 0)
			{
				Htab.push_back(kontener);

				plik >> kontener;
			}
			tab.push_back(Htab);

		}
	}
	else
	{
		std::cout << " nie mo¿na otworzyæ pliku" << std::endl;
		return 0;

	}
	check();
}


