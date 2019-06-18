// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneretedObjectV2.h"

// Sets default values
AGeneretedObjectV2::AGeneretedObjectV2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    
}

// Called when the game starts or when spawned
void AGeneretedObjectV2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGeneretedObjectV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FColliderStruct> AGeneretedObjectV2::ParseTxt(FString FilePath, FString FileName)
{
	std::string Path = std::string(TCHAR_TO_UTF8(*(FilePath + FileName)));
	std::ifstream file(Path);
	FColliderStruct ColliderStruct = FColliderStruct::FColliderStruct();
	TArray<FColliderStruct> ColliderStructArray;
	std::string curline;
	int avoidempty = -1;
	//std::ofstream log_file("C:\\Users\\Calculateur 02\\Desktop\\dwylans_awesome_logs.txt", std::ios::app);
	//log_file << "I'M ALIVE" << "\n"; //std::endl;
	
	while (std::getline(file, curline))
	{
		// Generate a Index ID
		if (firstToken(curline) == "o")
		{
			if (avoidempty != -1)
			{
				ColliderStructArray.Add(ColliderStruct);
				ColliderStruct = FColliderStruct::FColliderStruct();
			}
			avoidempty += 1;
			std::vector<std::string> spos;
			FVector vpos;
			split(tail(curline), spos, "_");

			//log_file << curline << "\n";

			ColliderStruct.Index = std::stoi(spos[1]);
		}
		// Generate a Vertex Position
		if (firstToken(curline) == "v")
		{
			std::vector<std::string> spos;
			FVector vpos;
			split(tail(curline), spos, " ");

			//log_file << curline << "\n";

			vpos.X = std::stof(spos[0]);
			vpos.Y = std::stof(spos[1]);
			vpos.Z = std::stof(spos[2]);

			ColliderStruct.Vertices.Add(vpos);
		}
		// Generate a Triangle Position
		if (firstToken(curline) == "f")
		{
			std::vector<std::string> spos;
			FVector tpos;
			split(tail(curline), spos, " ");

			//log_file << spos[0] << " " << spos[1] << " " << spos[2] << "\n";

			tpos.X = std::stoi(spos[0])-1;
			tpos.Y = std::stoi(spos[1])-1;
			tpos.Z = std::stoi(spos[2])-1;

			ColliderStruct.Triangles.Add(tpos.X);
			ColliderStruct.Triangles.Add(tpos.Y);
			ColliderStruct.Triangles.Add(tpos.Z);
		}
	}
	//log_file << "I'M DEAD" << std::endl;
	ColliderStructArray.Add(ColliderStruct);
	//log_file << "Size of element : " << ColliderStructArray.Num() << "\n";
	//log_file.close();
	file.close();
	return ColliderStructArray;
}

int AGeneretedObjectV2::RecupNbCollider(FString FilePath, FString FileName)
{
	std::string Path = std::string(TCHAR_TO_UTF8(*(FilePath + FileName)));
	std::ifstream file(Path);

	int NbCollider = 0;

	std::string curline;
	while (std::getline(file, curline))
	{
		// Generate a Index Position
		if (firstToken(curline) == "o")
		{
			NbCollider += 1;
		}
	}
	file.close();
	return NbCollider;
}

float AGeneretedObjectV2::LectureMeshDimension(FString FilePath, FString FileName)
{

	std::string Path = std::string(TCHAR_TO_UTF8(*(FilePath + FileName)));
	std::ifstream file(Path);

	float Dimension = 0;
	int i = 0;
	FVector2D Temp = FVector2D(0, 0);
	std::string curline;
	while (std::getline(file, curline))
	{
		Temp[i] = std::stof(curline);
		i += 1;
	}
	file.close();
	Dimension = Temp[0] + (Temp[1] - Temp[0]) / 2;
	return Dimension;
}

// Split a String into a string array at a given token
void AGeneretedObjectV2::split(const std::string &in, std::vector<std::string> &out, std::string token)
{
	out.clear();

	std::string temp;

	for (int i = 0; i < int(in.size()); i++)
	{
		std::string test = in.substr(i, token.size());

		if (test == token)
		{
			if (!temp.empty())
			{
				out.push_back(temp);
				temp.clear();
				i += (int)token.size() - 1;
			}
			else
			{
				out.push_back("");
			}
		}
		else if (i + token.size() >= in.size())
		{
			temp += in.substr(i, token.size());
			out.push_back(temp);
			break;
		}
		else
		{
			temp += in[i];
		}
	}
}

// Get tail of string after first token and possibly following spaces
std::string AGeneretedObjectV2::tail(const std::string &in)
{
	size_t token_start = in.find_first_not_of(" \t");
	size_t space_start = in.find_first_of(" \t", token_start);
	size_t tail_start = in.find_first_not_of(" \t", space_start);
	size_t tail_end = in.find_last_not_of(" \t");
	if (tail_start != std::string::npos && tail_end != std::string::npos)
	{
		return in.substr(tail_start, tail_end - tail_start + 1);
	}
	else if (tail_start != std::string::npos)
	{
		return in.substr(tail_start);
	}
	return "";
}

// Get first token of string
std::string AGeneretedObjectV2::firstToken(const std::string &in)
{
	if (!in.empty())
	{
		size_t token_start = in.find_first_not_of(" \t");
		size_t token_end = in.find_first_of(" \t", token_start);
		if (token_start != std::string::npos && token_end != std::string::npos)
		{
			return in.substr(token_start, token_end - token_start);
		}
		else if (token_start != std::string::npos)
		{
			return in.substr(token_start);
		}
	}
	return "";
}

// Generate a cross produect normal for a triangle
FVector AGeneretedObjectV2::GenTriNormal(FVector Vert1, FVector Vert2, FVector Vert3)
{
	FVector u = Vert2 - Vert1;
	FVector v = Vert3 - Vert1;

	FVector normal; 
	// Cross Product
	normal = FVector(u.Y * v.Z - u.Z * v.Y,
			u.Z * v.X - u.X * v.Z,
			u.X * v.Y - u.Y * v.X);

	return normal;
}
