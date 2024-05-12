#include <iostream>
#include <vector>
#include <map>
#include <set>

#include <algorithm> // for std::find



#define NO_OF_CHARS 256
 
bool areAnagram(char* str1, char* str2){

    // Create a count array and initialize 
    // all values as 0
    int count[NO_OF_CHARS] = { 0 };
    int i;
 
    // For each character in input strings, 
    // increment count in the corresponding 
    // count array
    for (i = 0; str1[i] && str2[i]; i++) {
        count[str1[i]]++;
        count[str2[i]]--;
    }

    // If both strings are of different length. 
    // Removing this condition will make the 
    // program fail for strings like "aaca" 
    // and "aca"
    if (str1[i] || str2[i])
        return false;
 
    // See if there is any non-zero value 
    // in count array
    for (i = 0; i < NO_OF_CHARS; i++)
        if (count[i])
            return false;
    return true;
}

// Gegeben ist ein Vector aus Anagrammen. Ein Anagramm ist ein Wort, welches durch umsortieren der Buchstaben sich ein anderes Wort ergibt.
// Baue aus dem gegebenen Vector eine Gruppe von Anagrammen auf, bei welchem die Wörter zusammenpassen.
// Zeigen diese Gruppe von Vectors an (die Anzeige-Reihenfolge ist egal).

int main()
{
    std::vector<std::string> strs = {"eat","tea","tan","ate","nat","bat"};
    // Ergebnis soll ungefähr so aussehen: { {"bat"}, {"nat","tan"}, {"ate","eat","tea"} }


    std::map< int, std::vector<std::string> > anagrammGroups{};
    //std::set< std::vector<std::string> > anagrammGroups{};

    unsigned int id_of_group{0}; // wird als Key für anagrammGroups verwendet
    std::size_t strs_len {strs.size()};
    std::vector<std::size_t> index_worked{};// enthählt Index von String, die schon in anagrammGroups hinzugefügt wurden


    //std::map< std::string, int > str_map{};

    for(std::size_t i{0}; i<strs_len - 1 ; i++ ){
        if(std::find(index_worked.begin(), index_worked.end(), i) != index_worked.end()){ //string an der Stelle i in Vector wurde schon abgearbeitet
            continue;
        }
        else{
            anagrammGroups.insert({++id_of_group, std::vector<std::string>{strs.at(i)}});// Es wird eine neue Gruppe (vector von String) von Anagram in den map unter dem Key id_of_group hinzugefügt
                                                                                         // diese neue Grupe wird in der actuelle Schleifendurchgang mit allen vorhandenen Anagramen ausgefüllt. 
                                                                                         // das Key id_of_group bleibt dans unverändert bis wir eine andere anagram Gruppe finden
            //index_worked.push_back(i); // nicht notwendig hier. Aber in der for-Scheleife mit j schon,
        }

        for(std::size_t j{i+1}; j<strs_len; j++){
            if(std::find(index_worked.begin(), index_worked.end(), j) != index_worked.end()){ //string an der Stelle i in Vector wurde schon abgearbeitet
                continue;
            }
            else{
                if( areAnagram(strs.at(i).data(), strs.at(j).data()) ){
                    anagrammGroups[id_of_group].push_back(strs.at(j)); // das key id_of_group ist die anagram Gruppe, die gerade ausgefüllt ist
                    index_worked.push_back(j);
                }
            }
        }     
    }
    



    
    for( const auto &group : anagrammGroups ){

        std::cout << "Group " << group.first << ":" << std::endl;
        for( const auto &word : group.second )
        {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
