#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <iterator>
#include <initializer_list>
#include <stack>

template <typename T>
class Graph
{
public:
   Graph(){}
   template<typename ...Args>
   Graph(Args&&...arg)
   {
          (void)std::initializer_list<int>{(VecGraph.push_back(std::forward<Args>(arg)), 0)...};
          SetSize(sizeof...(arg));
           
   }

   virtual ~Graph(){};
   void SetSize(int size_);
   const int GetSize() const {return size;} 
   void Output();
   void Resize();
   void bfs();
   void dfs();
   void Dijkstra(const size_t&);
    std::vector<T>& operator[](const int &index)
    {
       return VecGraph[index];
    } 
protected:
   std::vector<std::vector<T> > VecGraph;
   int size;
};


template <typename T>
void Graph<T>::SetSize(int size_)
{
   size=size_;
   Resize();
}

template <typename T>
void Graph<T>::Output()
{
   for(int i=0; i<size; ++i)
   {
      std::copy(VecGraph[i].begin(), VecGraph[i].end(), std::ostream_iterator<int>(std::cout, " "));
      std::cout<<std::endl;
   }
   for(int i=0; i<size; ++i)
   {
      for(int j=0; j<size; ++j)
      {
         if(VecGraph[i][j]==1)
            std::cout<<i+1<<" node is connected with "<< j+1 <<" node.\n";
      }
   }
}

template <typename T>
void Graph<T>::Resize()
{
   VecGraph.resize(size);
   for(int i=0; i<size; ++i)
      VecGraph[i].resize(size);
}

template <typename T>
void Graph<T>::bfs()
{
    std::queue<T> que{};
    std::vector<T> nodes(GetSize());
    for(size_t i = 0; i < GetSize(); ++i)
    {
        nodes[i] = 0;
    }
    que.push(VecGraph[0][0]);
    while(!que.empty())
    {
        T node = que.front();
        que.pop();
        nodes[node] = 2;
        for(size_t j = 0; j < GetSize(); ++j)
        {
            if(VecGraph[node][j] == 1 && nodes[j] == 0)
            {
                que.push(j);
                nodes[j] = 1;
            }
        }
        std::cout<< node + 1 <<std::endl;
    } 
}

template <typename T>
void Graph<T>::dfs()
{
    std::stack<T> Stack{};
    std::vector<T> nodes(GetSize());
    
  for (int i = 0; i < GetSize(); i++)
    nodes[i] = 0;
  Stack.push(0);
  while (!Stack.empty())
  { 
    int node = Stack.top(); 
    Stack.pop();
    if (nodes[node] == 2) continue;
    nodes[node] = 2;
    for (int j = GetSize() - 1; j >= 0; j--)
    { 
      if (VecGraph[node][j] == 1 && nodes[j] != 2)
      { 
        Stack.push(j); 
        nodes[j] = 1; 
      }
    }
    std::cout << node + 1 << std::endl; 
  }
}

template <typename T>
void Graph<T>::Dijkstra(const size_t& st)
{
    int distance[GetSize()], count, index, i, u, m=st+1;
	bool visited[GetSize()];
	for (i=0; i<GetSize(); i++)
	{
		distance[i]=std::numeric_limits<int>::max(); visited[i]=false;
	}
	distance[st]=0;
	for (count=0; count<GetSize()-1; count++)
	{
	int min=std::numeric_limits<int>::max();
	for (i=0; i<GetSize(); i++)
	if (!visited[i] && distance[i]<=min)
	{
	min=distance[i]; index=i;
	}
	u=index;
	visited[u]=true;
	for (i=0; i<GetSize(); i++)
	if (!visited[i] && VecGraph[u][i] && distance[u]!=std::numeric_limits<int>::max() &&
	distance[u]+VecGraph[u][i]<distance[i])
	distance[i]=distance[u]+VecGraph[u][i];
	}
	std::cout<<"—тоимость пути из начальной вершины до остальных:\t\n";
	for (i=0; i<GetSize(); i++) if (distance[i]!=std::numeric_limits<int>::max())
	std::cout<<m<<" > "<<i+1<<" = "<<distance[i]<<std::endl;
	else std::cout<<m<<" > "<<i+1<<" = "<<"маршрут недоступен"<<std::endl;
	}
int main()
{
	
}
