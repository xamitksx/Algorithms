#if 1
/* This is DB implementation with String Hash (using DJB2 function) DB has 5 fields all are string.
-- Add a entry in DB
void Add(char* name, char* number, char* birthday, char* email, char* memo);
-- Delete entries
int Delete(FIELD field, char* str);
-- change all DB records which have given str for field --- update there changefield by changestr 
int Change(FIELD field, char* str, FIELD changefield, char* changestr);
-- Search with any field and return -1 for no result -- if 1 or more result found return count + First value of Returnfield
RESULT Search(FIELD field, char* str, FIELD returnfield);
*/
#include <malloc.h>
#include <assert.h>
#include <cstdio>

typedef enum
{
	CMD_INIT,
	CMD_ADD,
	CMD_DELETE,
	CMD_CHANGE,
	CMD_SEARCH
} COMMAND;

typedef enum
{
	NAME,
	NUMBER,
	BIRTHDAY,
	EMAIL,
	MEMO
} FIELD;

typedef struct
{
	int count;
	char str[20];
} RESULT;

#define SZ 20
#define HASHSIZE 100002

typedef struct _rec {
	char data[5][SZ];
}REC;

typedef struct _llist {
	//char *data;
	REC * rec;
	struct _llist * next;
	struct _llist * prev;
}LL;
LL ** HashName = NULL;
LL ** HashNumb = NULL;
LL ** HashBday = NULL;
LL ** HashEmail = NULL;
LL ** HashMemo = NULL;

unsigned long getHashno(char * data)
{
	unsigned long hash = 5381;
	while (*data != '\0')
	{
		hash = (hash << 5) + hash + *data;  // mul by 33
		data++;
	}
	return hash%HASHSIZE;
}

int mystrCmp(char * str1, char * str2)
{
	while (*str1 == *str2)
	{
		if (*str1 == '\0' || *str2 == '\0')
			return *str1 - *str2;
		str1++;
		str2++;
	}
	return *str1 - *str2;
}
int mystrCpy(char * src, char * dst)
{
	int cnt = 0;
	while (*src != '\0')
	{
		*dst++ = *src++;
		cnt++;
	}
	*dst = '\0';
	return cnt;
}

void cleanHash(LL ** hash)
{
	for (int i = 0; i < HASHSIZE; i++)
	{
		if (hash[i])
		{
			LL * iter = hash[i];
			while (iter)
			{
				LL * todel = iter;
				iter = iter->next;
				free(todel);
			}
		}
	}
	free(hash);
}
void cleanHashwithRec(LL ** hash)
{
	for (int i = 0; i < HASHSIZE; i++)
	{
		if (hash[i])
		{
			LL * iter = hash[i];
			while (iter)
			{
				LL * todel = iter;
				iter = iter->next;
				free(todel->rec); // del Rec 
				free(todel);
			}
		}
	}
	free(hash);
}
void InitDB()
{
	if (HashName)
	{
		cleanHash(HashName);
	}

	if (HashNumb)
		cleanHash(HashNumb);
	if (HashBday)
		cleanHash(HashBday);
	if (HashMemo)
		cleanHash(HashMemo);
	// cleans rec also ;
	if (HashEmail)
		cleanHashwithRec(HashEmail);

	HashName = (LL **)calloc(HASHSIZE, sizeof(LL));
	HashNumb = (LL **)calloc(HASHSIZE, sizeof(LL));
	HashBday = (LL **)calloc(HASHSIZE, sizeof(LL));
	HashEmail = (LL **)calloc(HASHSIZE, sizeof(LL));
	HashMemo = (LL **)calloc(HASHSIZE, sizeof(LL));

}
LL ** getHashfrmType(FIELD field)
{
	switch (field)
	{
	case NAME:
		return HashName;
		break;
	case NUMBER:
		return HashNumb;
		break;
	case BIRTHDAY:
		return HashBday;
		break;
	case EMAIL:
		return HashEmail;
		break;
	case MEMO:
		return HashMemo;
		break;
	}
}
// allocates LL node and insets in specified hash 
void insertInHash(LL **hash, char * data, REC * rec)
{
	unsigned long index = getHashno(data);
	LL * temp = (LL*)calloc(1, sizeof(LL));
	temp->rec = rec;
	temp->next = hash[index];
	// insert at first node 
	if (hash[index] != NULL)
	{
		hash[index]->prev = temp;
	}
	hash[index] = temp;
}
// removes particular entry from hash  searches based on data
void removeFromHash(LL **hash, char * data, REC * rec)
{
	unsigned long index = getHashno(data);
	LL * iter = hash[index];
	assert(iter != NULL);
	while (iter)
	{
		if (iter->rec == rec)
		{
			if (iter->prev)
			{
				iter->prev->next = iter->next;
			}
			else // first node 
			{
				hash[index] = iter->next;
			}
			if (iter->next)
			{
				iter->next->prev = iter->prev;
			}
			free(iter);
			return;
		}
		iter = iter->next;
	}

}
void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
	REC * temp = (REC*)calloc(1, sizeof(REC));
	int ret = mystrCpy(name, temp->data[0]);
	ret = mystrCpy(number, temp->data[1]);
	ret = mystrCpy(birthday, temp->data[2]);
	ret = mystrCpy(email, temp->data[3]);
	ret = mystrCpy(memo, temp->data[4]);

	insertInHash(HashName, name, temp);
	insertInHash(HashNumb, number, temp);
	insertInHash(HashBday, birthday, temp);
	insertInHash(HashEmail, email, temp);
	insertInHash(HashMemo, memo, temp);
}
int Delete(FIELD field, char* str)
{
	int count = 0;
	LL** hash = getHashfrmType(field);
	unsigned long index = getHashno(str);
	LL * llPtr = hash[index];
	////
	while (llPtr)
	{
		int strcmp = mystrCmp(llPtr->rec->data[field], str);
		if (strcmp == 0)
		{
			count++;
			// delete the record
			REC * rectodelete = llPtr->rec;
			if (llPtr->prev)
			{
				llPtr->prev->next = llPtr->next;
			}
			else
			{
				hash[index] = llPtr->next;
			}
			if (llPtr->next)
			{
				llPtr->next->prev = llPtr->prev;
			}
			LL * toDelete = llPtr;
			llPtr = llPtr->next;
			free(toDelete);

			// loop for cleaning all hash
			for (int i = 0; i < 5; i++)
			{
				if (i != field)
				{
					LL** otherHash = getHashfrmType((FIELD)i);
					removeFromHash(otherHash, rectodelete->data[i], rectodelete);
				}
			}
			////remove from other hashes 
			// bug is here
			free(rectodelete);
		}
		else
		{
			llPtr = llPtr->next;
		}

	}
	return count;
}
int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
	int cnt = 0;
	LL** hash = getHashfrmType(field);
	unsigned long index = getHashno(str);
	LL * llPtr = hash[index];
	////
	while (llPtr)
	{
		int strcmp = mystrCmp(llPtr->rec->data[field], str);
		if (strcmp == 0)
		{
			cnt++;
			char oldStr[SZ];
			mystrCpy(llPtr->rec->data[changefield], oldStr);
			/// Updated  rec 
			mystrCpy(changestr, llPtr->rec->data[changefield]);
			REC * updatedRec = llPtr->rec;
			if (field != changefield)
			{
				/// update hash table of New  changefield
				LL** hashChagedField = getHashfrmType(changefield);
				// remove LL node from oldllPtr and insert in newllPtr
				removeFromHash(hashChagedField, oldStr, updatedRec);
				insertInHash(hashChagedField, changestr, updatedRec);
				llPtr = llPtr->next;
			}
			else
			{
				/// both fields are same
				// test
				unsigned long index = getHashno(str);
				unsigned long index2 = getHashno(changestr);
				// if (index == index2)  // for debugging
				// {
				//	 LL* nodeTofree = llPtr;
				// }
#if 1
				insertInHash(hash, changestr, updatedRec);
				if (llPtr->prev)
				{
					llPtr->prev->next = llPtr->next;
				}
				else // first node 
				{
					hash[index] = llPtr->next;
				}
				if (llPtr->next)
				{
					llPtr->next->prev = llPtr->prev;
				}
				LL* nodeTofree = llPtr;
				llPtr = llPtr->next;
				free(nodeTofree);
#endif
			}

		}// if strcmp
		else
		{
			llPtr = llPtr->next;
		}

	}

	return cnt;
}
RESULT Search(FIELD field, char* str, FIELD returnfield)
{
	/// debug

	RESULT rec;
	int cnt = 0;
	char * strField = NULL;
	LL** hash = getHashfrmType(field);
	unsigned long index = getHashno(str);
	LL * llPtr = hash[index];
	////
	while (llPtr)
	{
		int strcmp = mystrCmp(llPtr->rec->data[field], str);
		if (strcmp == 0)
		{
			cnt++;
			if (cnt == 1)
			{
				mystrCpy(llPtr->rec->data[returnfield], rec.str);
			}
		}
		llPtr = llPtr->next;
	}
	rec.count = cnt;
	return rec;

}
#endif
