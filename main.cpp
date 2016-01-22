/**
	Author		:	Pankaj Kataria
	Discription	:	A program to convert NFA to DFA + your
					life easy.
	Input 		:	For input a seprate file is being made as
					and the format for that file is defined as
					below

					No-of-nodes no-of-transitions no-of-symbols no-of-final-states
					final-states ...
					from where when
					...
					... 
**/
#include <bits/stdc++.h>

#define loop( container , it )	for( typeof(container.begin()) it = container.begin(); it != container.end(); it++)
#define present( container , x )	( (c).find(x) != (c).end()  )

typedef std :: map < std:: pair < int , char > , int > :: iterator mapiterator; 
typedef std :: set < int >  :: iterator maping_iterator;
using namespace std;

class Automata{
	public:
		//intialization
		Automata()
		{
			start=0;//starting state
			nodes=0;//total states
			total_transitions=0;//total transitions
			symbols=0;//total no of symbols
		}
		Automata( int start_state, int no_nodes, int t_transitions,int t_symbols )
		{
			start=start_state;//starting state
			nodes=no_nodes;//total states
			total_transitions=t_transitions;//total transitions
			symbols=t_symbols;//total no of symbols
		}
		//printing input symbols
		void print_symbols()
		{
			loop( input_symbols , it )
			{
				cout << *it <<endl;
			}
		}
		//adding a trasition
		void add(int from,int where, char when)
		{
			// cout<< "from : "<<from<<" where : "<<where<<" when : "<<when<<endl;
			transitions[make_pair(make_pair(from,when),where)]=1;
			input_symbols.insert(when);
		}
		//adding a final state
		void add_final_state(int finalstate)
		{
			final_states.push_back(finalstate);
		}
		//for outputting the dfa
		void output()
		{
			loop( transitions , it )
			{
				pair < pair < int , char > , int > p=it->first;
				printf("\t  %d %c %d\n",p.first.first,p.first.second,p.second);
			}
		}
		int check( set < int > &s)
		{
			loop( maping , s_it )
			{
				bool flag=false;
				maping_iterator it=s.begin(); 
				loop( s_it->second , v_it)
				{
					if( *v_it != *it)
					{
						flag=false;
					}
				}
				if( flag )
				{
					return ( s_it->first );
				}
				else
				{
					return flag;
				}
			}
		}
		void convert()//function to convert DFA to an NFA
		{
			Automata * dfa=new Automata();
			set < int > intial;
			intial.insert(1);
			maping.insert(pair< int , set < int > >(1,intial));
			
			int node_counter=1;//counter for addressing the nodes
			queue < int > q;//queue for storing the elemnets
			q.push(this->start);
			
			while( !q.empty() )
			{
				set < int > union_nodes;
				int current_node=q.front();
				// cout << "--------------------" << endl; 
				// cout << "current node : " << current_node << endl;
				q.pop();
				loop( input_symbols , input_it )//loop for the symbols
				{
					union_nodes.clear();
					loop( maping[current_node] , set_it )//loop for every element in the node
					{
						loop( transitions , t_it )//loop for transitions 
						{
							if( (t_it->first.first.second == *input_it) && (t_it->first.first.first == *set_it) )
							{
								// cout << "mapping size : "<< maping.size() << endl;
								// cout << t_it->first.first.second << " : " << t_it->first.first.first << " : " << *set_it << endl;
								union_nodes.insert(t_it->first.second);
							}
						}
					}
					// cout << "current symbol : "<<*input_it<<endl;
					// cout << "current node element : ";
					// loop( union_nodes , s_it )
					// {
					// 	cout << *s_it ;
					// }
					// cout << endl; 
					if( union_nodes.empty() )//union_nodes is empty
					{
						dfa->add(current_node,0,*input_it);
					}
					else
					{
						int index = this->check(union_nodes);
						if( index > 0 )//if the set gathered already exists
						{
							dfa->add(current_node,index,*input_it);
						}
						else
						{
							node_counter++;
							q.push(node_counter);
							maping[node_counter]= union_nodes;
							dfa->add(current_node,node_counter,*input_it);
						}
					}					
				}
			}
			cout << "\t----------" << endl;
			cout << "\tFinal Dfa " << endl;
			cout << "\t----------" << endl;
			dfa->output();
			//return dfa;
		}
	private:
		//data members
		map < pair < pair < int , char > , int > , int > transitions;//eg: q1 --a--> q2
		map < int , set < int > > maping;//mapping of state name to members in the set
		set < char > input_symbols;//set of input symbols 
		vector < int > final_states;//set of final states
		int start,nodes,symbols,total_transitions;
};
int main(){
	
	ifstream in("input.txt");//Input file

	int N;//no's of nodes
	int M;//no of Transitions
	int K;//no of symbols
	int F;//no of Final states
	int S;//Start State

	int X;//input
	int u;//input
	int v;//input
	char sym;//input symbol
	
	in >> N >> M >> K >> F >> S;//taking the input
	Automata *nfa=new Automata(S,N,M,K);//out dfa
	
	//Setting the final states
	for (int i = 0; i < F; ++i)
	{
		in >> X;
		nfa->add_final_state(X);
	}

	//Setting the trasitions
	while ( !in.eof() )
	{
		in >> u >> v >> sym;
		nfa->add(u,v,sym);
	}
	//Entered Automata
	cout << "\t---------" << endl;
	cout << "\tInput Nfa " << endl;
	cout << "\t---------" << endl;
	nfa->output();
	nfa->convert();
	return 0;
}