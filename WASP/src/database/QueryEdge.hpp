#ifndef QUERYEDGE_HPP_
#define QUERYEDGE_HPP_

#include <string>
#include <vector>
extern "C"{
#include "type.h"
}

using namespace std;
class QueryNode;
class AsyncRedisStore;
class TripleDB;
class QueryEdge{
	public:
		int tag, towardsJoint;
		dir_t d;
		vector<sid_t> bind_val;
		QueryNode *node;
		int exec_flag = 2; // 1 -- read index; 2 -- output result; 3 -- both; 0 -- neither
		
		vector<string> src_union_key;	
		//int is_key_new = 0;
		//vector<sid_t> candi_src_bind;

	public:
		QueryEdge(){}
		QueryEdge(int tag, dir_t d, int joint, vector<sid_t> bind_v)
			:tag(tag), d(d), towardsJoint(joint), bind_val(bind_v)
		{}

		virtual ~QueryEdge();

		int preprocess(int tgt_s,AsyncRedisStore* async_store);
		//int preprocess(int tgt_s, TripleDB* tripledb);
		/////////////////////////////
		template <typename Archive> void serialize(Archive &ar, const unsigned int version){
			ar & tag;	
			ar & towardsJoint;
			ar & d;
			ar & bind_val;
			ar & exec_flag;
			ar & node;
		}
		int parse_triples(int *tag, vector<const char*> *args);

		int parse_binds(vector<const char*> *args);

		int print(int indent);

};

#endif
