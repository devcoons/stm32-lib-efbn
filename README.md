# EXECUTE FUNCTION BY NAME

This library is needed whenever you want to call a function through an ID associated to it.
It is useful if you want to receive the ID through a message of any sort.

## Supported Hardware

- NUCLEO-H745ZI-Q


## How to use

- In your main, include `efbn.h`
- Create an instance of `efbn_t` to be used as the handler and afterwards create an array of `efbn_entry_t` (efbn_entry_t entries[]={entry1, entry2...}) and add all the functions you need. For each entry, define
	- `.id` : id of the function.
	- `.func` : pointer to the function.
	

For example:

```C

void f1(void* d,uint32_t sz)
{
	uint8_t* cd = (uint8_t*)d;
	printf("F1 %s\n",cd);
}
void f2(void* d,uint32_t sz)
{
	printf("F2\n");
}


//entries:

efbn_entry_t entries[] = 
{
	{ .id = 0x000000F1, .func = f1 },
	{ .id = 0x000000F2, .func = f2 }
};

//handler:

efbn_t h_efbn =
{
	.entries = entries,
	.entries_cnt = 2
};

```



### Functions Guide

- `efbn_init` : initializes the structure `efbn_entry_t` that contains the functions and their IDs.
- `efbn_exists_by_id` : checks wether a function associated with a specified ID has been defined or not.
- `efbn_exists_by_address` : checks wether a function associated with a specified address has been defined or not.
- `efbn_execute`: executes the function associated with a specified ID.


## Example

In this example, the functions are tested with the structure created above
```C


int main(void)
{
	
	i_status r1 = efbn_exists_by_id(&h_efbn,0x000000F0); //returns I_NOTEXISTS
	i_status r2 = efbn_exists_by_id(&h_efbn,0x000000F1); //returns I_EXISTS
	i_status r3 = efbn_exists_by_address(&h_efbn,3424); //returns I_NOTEXISTS
	i_status r4 = efbn_exists_by_address(&h_efbn,(uint32_t)f2); //returns I_EXISTS

	i_status r5 = efbn_execute(&h_efbn,0x000000F1,"hello",6); //prints "Hello"
	i_status r6 = efbn_execute(&h_efbn,0x000000F9,NULL,0); //returns I_INVALID
	
	return 0;
}
```
