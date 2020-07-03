# CharacterTreeSerialization

complier used: g++ (MinGW.org GCC Build-20200227-1) 9.2.0

command to complie: g++ Main.cpp
command to execute: 
1. a create csv-file.csv serialized-output.bin
2. a load serialized-output.bin
++++++++++++++++++++++++++++++++++++++++++++++++++++
steps

Trie t1 = new Trie();
for(string each : input){
  t1->insert(each);
}
Trie t2 = t1->deserialize(t1->serialize());

  
