#include "System.h"


const string defKey = "\n";


void Manager::fill(ifstream & in)
{
	string buffer;
	while (!in.eof())
	{
		getline(in, buffer);
		if (!buffer.compare("[zones]")) addZones(in);
		//else if (!buffer.compare("[keys]")) addKey(in);
	}
}

void Manager::addZones(ifstream & in)
{
	string lhs_Zone;
	string rhs_Zone;
	string key;
	string buffer;


	while (!in.eof()) {
		if (in.peek() == '\n') {
			in.get();
			addKey(in);
			return;
		}

		getline(in, buffer, ' ');
		lhs_Zone = buffer;

		getline(in, buffer, ' ');
		buffer.clear();

		while (in.peek() != '[' && in.peek() != ';')
		{
			char ch;
			in.get(ch);
			buffer += ch;
		}

		if (buffer.back() == ' ') buffer.pop_back();
		rhs_Zone = buffer;
		buffer.clear();

		if (in.peek() == '[') {
			in.get();
			getline(in, buffer, ']');
		}
		key = buffer;
		in.get();

		//holder.insert(make_pair(lhs_Zone,Zone()));
		
		if(holder.find(lhs_Zone) == holder.end()) holder.insert(make_pair(lhs_Zone, Zone()));
		if (holder.find(rhs_Zone) == holder.end()) holder.insert(make_pair(rhs_Zone, Zone()));

		if (key.size() > 0) {
			holder[lhs_Zone].children.push_back(make_pair(rhs_Zone, key));
		}
		else holder[lhs_Zone].children.push_back(make_pair(rhs_Zone, defKey));
		in.get();
	}
}

void Manager::addKey(ifstream & in)
{
	string Zone;
	string key;
	string buffer;

	getline(in, buffer);
	buffer.clear();

	while (!in.eof())
	{
		if (in.peek() == '\n') {
			while (in.peek() == '\n')
			{
				in.get();
			}
			continue;
		}
		getline(in, buffer, '-');
		buffer.pop_back();
		key = buffer;

		getline(in, buffer, ' ');

		getline(in, buffer, ';');
		Zone = buffer;

		holder[Zone].keys.push_back(key);
	//	in.get();
	}
}

void Manager::BFS(string& start, unordered_set<string>& keyChain)
{
	unordered_set<string> visited;
	queue<string> queue;
	queue.push(start);

	while (!queue.empty())
	{
		start = queue.front();
		visited.insert(start);

		holder[start].isAccesable = true;

		for (string& key : holder[start].keys) {
			if (keyChain.find(key) == keyChain.end()) {
				unordered_set<string>& newKeyChain = keyChain;
				newKeyChain.insert(key);
				BFS(start, newKeyChain);
			}
		}

		for (pair<string,string> child : holder[start].children)
		{
			if (visited.find(child.first) == visited.end())
			{
				if ((child.second == defKey) || (keyChain.find(child.second) != keyChain.end())) {
					holder[child.first].isAccesable = true;
					visited.insert(child.first);
					queue.push(child.first);
				}
			}
		}
		queue.pop();
	}
}

void Manager::createOutCode()
{
	std::ofstream out("output.txt");
	if (!out) {
		std::cout << "Couldn't create file \n";
		return;
	}

	out << "digraph { \n";
	for (const std::pair<std::string, Zone>& curr : holder) {

		if (!curr.second.isAccesable || curr.second.keys.size() > 0) {
			out << "\t" << curr.first << " [";

			if (curr.second.keys.size() > 0) {
				out << "label = \"" << curr.first;
				for (const std::string& key : curr.second.keys)
					out << "\\l" << key;
				out << '\"';
			}

			if (!curr.second.isAccesable) {
				if (curr.second.keys.size() > 0)
					out << ", ";
				out << "color = red, style = filled, fillcolor = \"#ffefef\"";
			}
			out << "];" << std::endl;

		}

		if (curr.second.children.size() > 0) {
			for (const std::pair<std::string, std::string>& child : curr.second.children) {
				out << "\t" << curr.first << " -> " << child.first;
				if (child.second != defKey)
					out << " [label = \"" << child.second << "\"]";
				out << ';' << std::endl;
			}
		}

		out << std::endl;

	}

	out << '}';
	out.close();
}
