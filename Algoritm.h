#pragma once

#include <C:\Users\user\Desktop\lab2\lab2\Map.h>

class Algoritm
{
public:
	string encode(string toEncode);
	string encodeReview(string toEncode);
	void printCodes();
	string decode(string toDecode);
	string decodeReview(string toDecode);

private:
	struct Node
	{
		string name;
		string code;
		unsigned int amount;
		Node* _1;
		Node* _0;
	};

	void coder(Node& node, string code);

	List<Node> alphabet;
};

string Algoritm::encode(string input)
{
	Map<char, unsigned int> composition;
	for (unsigned int i = 0; i < input.size(); ++i)
	{
		char temp = input.at(i);

		if (composition.find(temp) == NULL)
			composition.insert(temp, 1);
		else
			composition.change(temp, composition.find(temp) + 1);
	}
	alphabet.clear();

	List<char> names;
	composition.get_keys(names);
	List<unsigned int> weights;
	composition.get_values(weights);

	for (unsigned int i = 0; i < names.GetSize(); ++i)
	{
		Node temp;
		temp.name = names[i];
		temp.amount = weights[i];
		alphabet.push_back(temp);
	}

	if (alphabet.GetSize() <= 2)
	{
		for (unsigned int i = 0; i < alphabet.GetSize(); ++i)
			alphabet[i].code = i;

		string answer;
		while (input.size() > 0)
			for (unsigned int i = 0; i < alphabet.GetSize(); ++i)
				if (alphabet[i].name[0] == input[0])
				{
					answer += alphabet[i].code;
					input.erase(0, 1);
					break;
				}
		return answer;
	}

	List<Node> allNodes;

	while (alphabet.GetSize() > 1)
	{
		Node* smallest1;
		Node* smallest2;
		if (alphabet[0].amount < alphabet[1].amount)
		{
			smallest1 = &alphabet[0];
			smallest2 = &alphabet[1];
		}
		else
		{
			smallest1 = &alphabet[1];
			smallest2 = &alphabet[0];
		}

		for (unsigned int i = 2; i < alphabet.GetSize(); ++i)
		{
			if (alphabet[i].amount < smallest1->amount)
			{
				smallest2 = smallest1;
				smallest1 = &alphabet[i];
			}
			else if (alphabet[i].amount < smallest2->amount)
				smallest2 = &alphabet[i];
		}
		Node temp;

		temp.name = smallest2->name;
		temp.name.append(smallest1->name);

		allNodes.push_back(*smallest2);
		temp._1 = &allNodes[allNodes.GetSize() - 1];

		allNodes.push_back(*smallest1);
		temp._0 = &allNodes[allNodes.GetSize() - 1];

		temp.amount = temp._0->amount + temp._1->amount;

		if (smallest1 < smallest2)
		{
			for (unsigned int i = 0; i < alphabet.GetSize(); ++i)
				if (&alphabet[i] == smallest2)
					alphabet.removeAt(i);
			for (unsigned int i = 0; i < alphabet.GetSize(); ++i)
				if (&alphabet[i] == smallest1)
					alphabet.removeAt(i);
		}
		else
		{
			for (unsigned int i = 0; i < alphabet.GetSize(); ++i)
				if (&alphabet[i] == smallest1)
					alphabet.removeAt(i);
			for (unsigned int i = 0; i < alphabet.GetSize(); ++i)
				if (&alphabet[i] == smallest2)
					alphabet.removeAt(i);
		}

		alphabet.push_back(temp);
	}

	coder(alphabet[0], "");

	alphabet.clear();



	for (unsigned int i = 0; i < allNodes.GetSize(); i++)
		if (allNodes[i].name.size() == 1)
			alphabet.push_back(allNodes[i]);

	string answer;
	while (input.size() > 0)
		for (unsigned int i = 0; i < alphabet.GetSize(); ++i)
			if (alphabet[i].name[0] == input[0])
			{
				answer += alphabet[i].code;
				input.erase(0, 1);
				break;
			}
	return answer;
}

string Algoritm::encodeReview(string input)
{
	Map<char, unsigned int> composition;
	for (unsigned int i = 0; i < input.size(); ++i)
	{
		char temp = input.at(i);

		if (composition.find(temp) == NULL)
			composition.insert(temp, 1);
		else
			composition.change(temp, composition.find(temp) + 1);
	}
	cout << input << endl;
	cout << "Contains:" << endl;
	composition.printList();

	string answer = encode(input);

	short preWeight = input.size() * 8;
	double postweight = answer.size();
	auto rate = (1 - postweight / preWeight) * 100;
	cout << "Initial text weight: " << preWeight << " bytes, code weight: " << postweight << " bytes, compression rate: " << rate << " %" << endl;

	cout << endl << "Encoded:" << endl << answer << endl;
	return answer;
}

void Algoritm::printCodes()
{
	for (unsigned int i = 0; i < alphabet.GetSize(); i++)
		cout << alphabet[i].name << " - " << alphabet[i].code << endl;
}

string Algoritm::decode(string input)
{
	if (alphabet.GetSize() == 0)
		throw exception("Attempt to decode without alphabet");
	string current;
	string answer;
	while (input.size() > 0)
	{
		current += input[0];
		input.erase(0, 1);
		for (unsigned int i = 0; i < alphabet.GetSize(); ++i)
			if (alphabet[i].code == current)
			{
				answer += alphabet[i].name;
				current.clear();
				if (input.size() == 0)
					return answer;
			}

	}
	throw exception("Couldn't decode");
}

string Algoritm::decodeReview(string input)
{
	string answer = decode(input);
	short preWeight = answer.size() * 8;
	double postweight = input.size();
	auto rate = (1 - postweight / preWeight) * 100;
	cout << "Initial text weight: " << preWeight << " bytes, code weight: " << postweight << " bytes, compression rate: " << rate << " %" << endl;

	cout << endl << "Decoded:" << endl << answer << endl;
	return answer;
}

void Algoritm::coder(Node& node, string code)
{
	if (node.name.size() == 1)
	{
		node.code = code;
		return;
	}
	string temp0 = code;
	temp0.append("0");
	coder(*node._0, temp0);
	string temp1 = code;
	temp1.append("1");
	coder(*node._1, temp1);
}