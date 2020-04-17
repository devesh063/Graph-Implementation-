/* Graph implementation and different operation performed */
#include <stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
struct edge;
struct node
{
	struct node *next;
	int name;
	struct edge *adj;
}*start=NULL;

struct edge
{
	int dest;
	struct edge *link;
};
struct node *find(int item);


void insert_node(int node_name)
{
	struct node *tmp,*ptr;
	tmp=(struct node *)malloc(sizeof(struct node));
	tmp->name=node_name;
	tmp->next=NULL;
	tmp->adj=NULL;

	if(start==NULL)
	{
		start=tmp;
		return;
	}
	ptr=start;
	while( ptr->next!=NULL)
		ptr=ptr->next;
	ptr->next=tmp;
}/*End of insert_node()*/

void delete_node(int u)
{
	struct node *tmp,*q;
	if(start->name == u)
	{
		tmp=start;
		start=start->next;  /* first element deleted */
		free(tmp);
		return;
	}
	q=start;
	while(q->next->next != NULL)
	{
		if(q->next->name==u)     /* element deleted in between */
		{
			tmp=q->next;
			q->next=tmp->next;
			free(tmp);
			return;
		}
		q=q->next;
	}/*End of while*/
	if(q->next->name==u)    /* last element deleted */
	{
		tmp=q->next;
		free(tmp);
		q->next=NULL;
	}
}/*End of delete_node()*/

void delnode_edge(int u)
{
	struct node *ptr;
	struct edge *q,*start_edge,*tmp;
	ptr=start;
	while(ptr!=NULL)
	{
		/* ptr->adj points to first node of edge linked list */
		if(ptr->adj->dest == u)
		{
			tmp=ptr->adj;
			ptr->adj=ptr->adj->link;  /* first element deleted */
			free(tmp);
			continue; /* continue searching in another edge lists */
		}
		q=ptr->adj;
		while(q->link->link != NULL)
		{
			if(q->link->dest==u)  /* element deleted in between */
			{
				tmp=q->link;
				q->link=tmp->link;
				free(tmp);
				continue;
			}
			q=q->link;
		}/*End of while*/
		if(q->link->dest==u)    /* last element deleted */
		{
			tmp=q->link;
			free(tmp);
			q->link=NULL;
		}
		ptr=ptr->next;
	}/*End of while*/
}/*End of delnode_edge()*/

void insert_edge(int u,int v)
{
	struct node *locu,*locv;
	struct edge *ptr,*tmp;
	locu=find(u);
	locv=find(v);

	if(locu==NULL )
	{
		printf("Source node not present ,first insert node %d\n",u);
		return;
	}
	if(locv==NULL )
	{
		printf("Destination node not present ,first insert node %d\n",v);
		return;
	}
	tmp=(struct edge *)malloc(sizeof(struct edge));
	tmp->dest=v;
	tmp->link=NULL;


	if(locu->adj==NULL)   /* item added at the begining */
	{
		 locu->adj=tmp;
		  return;
	}
	ptr=locu->adj;
	while(ptr->link!=NULL)
		ptr=ptr->link;
	ptr->link=tmp;

}/*End of insert_edge()*/

struct node *find(int item)
{
	struct node *ptr,*loc;
	ptr=start;
	while(ptr!=NULL)
	{
		if(item==ptr->name)
		{
			loc=ptr;
			return loc;
		}
		else
			ptr=ptr->next;
	}
	loc=NULL;
	return loc;
}/*End of find()*/

void del_edge(int u,int v)
{
	struct node *locu,*locv;
	struct edge *ptr,*tmp,*q;
	locu=find(u);

	if(locu==NULL )
	{
		printf("Source node not present\n");
		return;
	}

	if(locu->adj->dest == v)
	{
		tmp=locu->adj;
		locu->adj=locu->adj->link;  /* first element deleted */
		free(tmp);
		return;
	}
	q=locu->adj;
	while(q->link->link != NULL)
	{
		if(q->link->dest==v)  /* element deleted in between */
		{
			tmp=q->link;
			q->link=tmp->link;
			free(tmp);
			return;
		}
		q=q->link;
	}/*End of while*/
	if(q->link->dest==v)    /* last element deleted */
	{
		tmp=q->link;
		free(tmp);
		q->link=NULL;
		return;
	}
	printf("This edge not present in the graph\n");
}/*End of del_edge()*/

void display()
{
	struct node *ptr;
	struct edge *q;

	ptr=start;
	while(ptr!=NULL)
	{
		printf("%d ->",ptr->name);
		q=ptr->adj;
		while(q!=NULL)
		{
			printf(" %d",q->dest);
			q=q->link;
		}
		printf("\n");
		ptr=ptr->next;
	 }
}
int main()
{
	int choice;
	int node,origin,destin;
	while(1)
	{
		printf("0.Insert a node\n");
		printf("1.Create an edge between two nodes\n");
		printf("2.Remove an edge between two nodes. \n");
		printf("3.Degree of particular node\n");
		printf("4.create node\n");
		printf("5.Delete node.\n");
		printf("6.display\n");
		printf("7.exit\n");
		printf("Enter your choice:\n");
		scanf("%d",&choice);
		switch(choice)
		{
		 
		 case 1:
		       
			printf("Enter an edge to be inserted:\n");
			scanf("%d",&origin);
                        scanf("%d",&destin);
			insert_edge(origin,destin);
			break;
		 case 5:
			printf("Enter a node to be deleted:\n");
			
			scanf("%d",&node);
			/*This fn deletes the node from header node list*/
			delete_node(node);
			/* This fn deletes all edges coming to this node */
			delnode_edge(node);
			break;
		 case 4:
		       printf("Enter a node to be inserted:\n");
		       
		       scanf("%d",&node);
		       insert_node(node);
		       break;
		
		 case 2:
			printf("Enter an edge to be deleted:\n");
			
			scanf("%d",&origin);
                        scanf("%d",&destin);
			del_edge(origin,destin);
			break;
		 case 6:
			display();
			break;
		 case 7:
		        exit(0);
			break;
		 default:
			printf("Wrong choice\n");
			break;
		 case 0:
		        
			printf("Enter a node to be inserted:\n");
			scanf("%d",&node);
			insert_node(node);
			break;
		 }
	}
}
