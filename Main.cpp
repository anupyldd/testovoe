/* 
 * ����� ������������ ��������� ��������� ���������� ������� �������,
 * ������� ����� �������������� � ����������� �� ����,
 * ��� ���������� ��� "����������� ���������".
 * 
 * -------------
 * 
 * ������ �������� ������� �������, ����������� �������� ������������
 * ���������� ����, ���������� �� �� ��������.
 * 
 * ������ �������� ��������� �������� � �������� �������, �������
 * ��������� �������� �������� ������ �����.
 * 
 * ������ �������� ��������� �������� ������� ����, ������������ ��
 * ���������, � ��������� ���� ������.
 * 
 * -------------
 * 
 * ��������� ���������� ������� ������ Route, � �������� ����������
 * ������� � ���������� ��������� << ��� �������� ������.
 * 
 * � ���� ������������ ���������� C++20.
 * 
 * -------------
 * 
 * ���������� ����������:
 * - ������: 29 �����, 114 ��������, 11 ����
 * - ������: 25 �����, 90 ��������, 5 ����
 * - ������: 31.5 �����, 133 ��������, 10 ����
 * 
 * ������ �������� ��������� �������� ����������� ��� � ������������� �������,
 * ��� � � ��������� �������� ���������� ����.
 */

#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <iostream>
#include <numeric>
#include <format>

namespace test
{
	// ��������� ���� �������� ��� �������� �������������, �� ����� ����
	// ������� �� ������ ��������� �������� � ��
	constexpr float VISIT_TIME = 48.0f;
	constexpr float SLEEP_TIME = 16.0f;

	struct Place
	{
		std::string	name;
		float		time;
		int			value;
	};

	const std::vector<Place> places =
	{
		{	"Isaakievskij sobor",								5.0f,	10	},
		{	"Ermitazh",											8.0f,	11	},
		{	"Kunstkamera",										3.5f,	4	},
		{	"Petropavlovskaya krepost",							10.0f,	7	},
		{	"Leningradskij zoopark",							9.0f,	15	},
		{	"Mednyj vsadnik",									1.0f,	17	},
		{	"Kazanskij sobor",									4.0f,	3	},
		{	"Spas na Krovi",									2.0f,	9	},
		{	"Zimnij dvorec Petra I",							7.0f,	12	},
		{	"Zoologicheskij muzej",								5.5f,	6	},
		{	"Muzej oborony i blokady Leningrada",				2.0f,	19	},
		{	"Russkij muzej",									5.0f,	8	},
		{	"Navestit druzej",									12.0f,	20	},
		{	"Muzej voskovyh figur",								2.0f,	13	},
		{	"Literaturno-memorialnyj muzej F.M. Dostoevskogo",	4.0f,	2	},
		{	"Ekaterininskij dvorec",							1.5f,	5	},
		{	"Peterburgskij muzej kukol",						1.0f,	14	},
		{	"Muzej mikrominiatyury \"Russkij Levsha\"",			3.0f,	18	},
		{	"Vserossijskij muzej A.S.Pushkina i filialy",		6.0f,	1	},
		{	"Muzej sovremennogo iskusstva Erarta",				7.0f,	16	}
	};

	struct Route
	{
		std::vector<Place>	places;

	public:
		friend std::ostream& operator<<(std::ostream& os, const Route& r)
		{
			os << std::format("Total time: {}; Total value: {}; Places visited: {}\n",
				std::accumulate(r.places.begin(), r.places.end(), 0.0f, [](float t, const Place& p) { return t + p.time; }),
				std::accumulate(r.places.begin(), r.places.end(), 0, [](int v, const Place& p) { return v + p.value; }),
				r.places.size());
			for (size_t i = 0; i < r.places.size(); ++i) os << std::format(" - {} ({}h, {})", r.places[i].name, r.places[i].time, r.places[i].value)
				<< ((i == (r.places.size() - 1)) ? "" : ", \n");
			return os;
		}
	};

	// ��������� ����������� ��� ����������
	struct CompTimeLess
	{
		bool operator()(const Place& p1, const Place& p2) const { return p1.time < p2.time; }
	} CTL;
	struct CompTimeGreater
	{
		bool operator()(const Place& p1, const Place& p2) const { return p1.time > p2.time; }
	} CTG;
	struct CompValueLess
	{
		bool operator()(const Place& p1, const Place& p2) const { return p1.value < p2.value; }
	} CVL;
	struct CompValueGreater
	{
		bool operator()(const Place& p1, const Place& p2) const { return p1.value > p2.value; }
	} CVG;

	// ������ ��������
	Route VisitMostPlaces()
	{
		Route res;
		float time = VISIT_TIME - SLEEP_TIME;
		std::vector<Place> temp = places;

		// ������ ���������� �� ������ �� ��������� � ������
		// ������, ������ � ������ � ����� ������� �������
		// ������, ��������� �� ��������� ���������� ��������.
		// � ������ ������������� ������� ����������, ������ 
		// ���������� ������ ������������ stable_sort
		//std::sort(temp.begin(), temp.end(), CVG);
		std::sort(temp.begin(), temp.end(), CTL);

		// ���������� ���� � ������� � �������� ���������� �������
		float accTime = 0;
		for (const auto& p : temp)
		{
			accTime += p.time;
			if (accTime <= time) res.places.push_back(p);
			else break;
		}

		return res;
	}

	// ������ ��������
	Route VisitByValue()
	{
		Route res;
		float time = VISIT_TIME - SLEEP_TIME;
		std::vector<Place> temp = places;

		// �� �� �������� � �����������, ��� � � ������ ���������
		//std::sort(temp.begin(), temp.end(), CTL);
		std::stable_sort(temp.begin(), temp.end(), CVG);

		float accTime = 0;
		for (const auto& p : temp)
		{
			accTime += p.time;
			if (accTime <= time) res.places.push_back(p);
			else break;
		}

		return res;
	}

	// ������ ��������
	Route VisitByHourValue()
	{
		Route res;
		float time = VISIT_TIME - SLEEP_TIME;

		// ���������, ������� �������� ��������� �� ����� �
		// �������� � ��� ��� ������� �����.
		// ����������� �������, �� �����, ���������, ���������
		// �� non-owning. �� ���� �� ������� �� ��������� ����������
		struct PlaceHV
		{
			const Place*	place;
			float			hourVal;
		public:
			PlaceHV(const Place& pl) : place(&pl) { hourVal = pl.value / pl.time; }
		};

		std::vector<PlaceHV> placesHV;
		for (const auto& p : places) { placesHV.emplace_back(p); }
		
		// ���������� ��� ��������� �������� � ���
		struct CompHVGreater
		{
			bool operator()(const PlaceHV& p1, const PlaceHV& p2) const { return p1.hourVal > p2.hourVal; }
		} CHVG;

		std::sort(placesHV.begin(), placesHV.end(), CHVG);

		float accTime = 0;
		for (const auto& p : placesHV)
		{
			accTime += p.place->time;
			if (accTime <= time) res.places.push_back(*p.place);
			else break;
		}

		return res;
	}
}

int main()
{
	
	std::cout << "\n [ VisitMostPlaces ] \n";
	std::cout << test::VisitMostPlaces();

	std::cout << "\n\n=================================\n\n";
	std::cout << "\n [ VisitByValue ] \n";
	std::cout << test::VisitByValue();

	std::cout << "\n\n=================================\n\n";
	std::cout << "\n [ VisitByHourValue ] \n";
	std::cout << test::VisitByHourValue();
}