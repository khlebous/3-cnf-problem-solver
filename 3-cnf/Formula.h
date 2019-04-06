#pragma once
#include <vector>
#include <unordered_set>
#include <sstream>
#include "Clause.h"
using namespace std;

class Formula
{
private:
	vector<Clause> clauses;

public:
	Formula() {}
	Formula(vector<Clause>& const _clauses)
	{
		clauses.clear();
		for (auto const &c : _clauses)
			clauses.push_back(c);
	}
	Formula(const Formula & f)
	{
		clauses.clear();
		for (auto const &c : f.clauses)
			clauses.push_back(c);
	}
	~Formula()
	{
		clauses.clear();
	}

	const Clause& operator[](size_t nr) const { return clauses[nr]; }
	Formula& operator=(const Formula& f)
	{
		if (this != &f)
		{
			clauses.clear();

			for (auto const &c : f.clauses)
				clauses.push_back(c);
		}
		
		return *this;
	}
	
	size_t ClausesCount() const { return clauses.size(); }
	string ToString() const
	{
		std::stringstream ss;
		if (clauses.size() == 0)
		{
			ss << "size == 0";
			return ss.str();
		}

		for (size_t i = 0; i < ClausesCount(); i++)
			{
			ss << "( " << clauses[i].ToString() << " )";
				if (i != ClausesCount() -1)
					ss << " ^ ";
			}

		return ss.str();
	}
	unordered_set<int> GetLiterals() const
	{
		unordered_set<int> literals;
		for (size_t i = 0; i < clauses.size(); i++)
			for (size_t j = 0; j < clauses[i].Size(); j++)
				literals.insert(abs(clauses[i][j]));

		return literals;
	}
	bool SubstituteTrue(int nr, Formula& f) const
	{
		vector<Clause> v;

		for (size_t i = 0; i < ClausesCount(); i++)
		{
			Clause c;
			switch (clauses[i].SubstituteTrue(nr, c))
			{
			case ClauseState::NEVER:
				return false;
				break;
			case ClauseState::UNKNOWN:
				v.push_back(c);
				break;
			default:
				break;
			}
		}

		if (v.size() == 0)
			return true;

		f = Formula(v);

		return false;
	}
};
