#pragma once
#include "Formula.h"
#include "Clause.h"

class Parser
{
private:
	static bool CanCreateClause(const vector<int>& v)
	{
		return v.size() > 0 && v.size() < 4;
	}

public:

	static bool TryParseStringToInt(string s, int& i)
	{
		size_t idx = 0;

		bool negate = (s[idx] == '-');
		if (s[idx] == '+' || s[idx] == '-')
			idx++;

		if (s[idx] == '\0')
			return false;

		int result = 0;
		for (size_t i = idx; i < s.size(); i++)
		{
			if (s[i] >= '0' && s[i] <= '9')
				result = result * 10 + (s[i] - '0');
			else
				return false;
		}
		i = negate ? -result : result;

		return true;
	}

	static bool TryParseStringToClause(string line, char delimeter, Clause & clause)
	{
		if (line == "")
			return false;

		size_t startIdx = 0;
		vector<int> v;

		size_t i = 0;
		for (; i < line.size(); i++)
		{
			if (line[i] == delimeter)
			{
				if (startIdx == i)
				{
					startIdx++;
					continue;
				}
				else
				{
					string toParse = line.substr(startIdx, i - startIdx);
					int parsed;
					if (!TryParseStringToInt(toParse, parsed))
						return false;
					v.push_back(parsed);
					startIdx = i + 1;
				}
			}
		}
		if (startIdx < i)
		{
			string toParse = line.substr(startIdx, i - startIdx);
			int parsed;
			if (!TryParseStringToInt(toParse, parsed))
				return false;
			v.push_back(parsed);
		}

		if (!CanCreateClause(v))
			return false;

		clause = Clause(v);

		return true;
	}

	static bool TryParseStringToFormula(vector<string>& const data,	char delemiter,
		Formula& formula)
	{
		if (data.size() == 0)
			return false;

		vector<Clause> clauses;
		for (auto const& s : data)
		{
			Clause clause;
			if (!TryParseStringToClause(s, delemiter, clause))
				return false;

			clauses.push_back(clause);
		}
		formula = Formula(clauses);

		return true;
	}
};
