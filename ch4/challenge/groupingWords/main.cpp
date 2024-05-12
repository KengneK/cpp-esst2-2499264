#include <iostream>
#include <vector>
#include <map>
#include <set>

#include <algorithm> // for std::find
#include <chrono>

#define with_set 2 // o-> with std::map. 
                   // 1 -> with std::set . 
                   // 2-> Lösung des Kursdozent
#define with_map_int_string 1 // Benutzen NUR in Block bei with_set == 0 
                              // with_map_int_string = 1 -> benutzung von std::map< int, std::vector<std::string> >. 
                              // with_map_int_string = 0 -> benutzung von std::map< std::string, std::vector<std::string> >

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

    std::chrono::duration<double, std::milli> duration_time{};
    auto t1 = std::chrono::high_resolution_clock::now();


#if(with_set == 0)

    #if(with_map_int_string == 1)
    std::map< int, std::vector<std::string> > anagrammGroups{};
    unsigned int id_of_group{0}; // wird als Key für anagrammGroups verwendet
    #elif(with_map_int_string == 0)
    std::map< std::string, std::vector<std::string> > anagrammGroups{};
    std::string id_of_group{}; // wird als Key für anagrammGroups verwendet
    #endif

    std::size_t strs_len {strs.size()};
    std::vector<std::size_t> index_worked{};// enthählt Index von String, die schon in anagrammGroups hinzugefügt wurden

    for(std::size_t i{0}; i<strs_len ; i++ ){
        if(std::find(index_worked.begin(), index_worked.end(), i) != index_worked.end()){ //string an der Stelle i in Vector wurde schon zu einer angram groupe hinzugefügt. Keine Weitere Bearbeitung des gleichen Strings
            continue;
        }
        else{
            #if(with_map_int_string == 1)
            anagrammGroups.insert({++id_of_group, std::vector<std::string>{strs.at(i)}});// Es wird eine neue Gruppe (vector von String) von Anagram in den map unter dem Key id_of_group hinzugefügt
                                                                                         // diese neue Grupe wird in der actuelle Schleifendurchgang mit allen vorhandenen Anagramen ausgefüllt. 
                                                                                         // das Key id_of_group bleibt dans unverändert bis wir eine andere anagram Gruppe finden
            
            #elif(with_map_int_string == 0)
            //anagrammGroups.insert({id_of_group = strs.at(i), std::vector<std::string>{strs.at(i)}}) // ok
            id_of_group = strs.at(i);
            anagrammGroups.insert({id_of_group, std::vector<std::string>{strs.at(i)}});// Es wird eine neue Gruppe (vector von String) von Anagram in den map unter dem Key id_of_group hinzugefügt
                                                                                         // diese neue Grupe wird in der actuelle Schleifendurchgang mit allen vorhandenen Anagramen ausgefüllt. 
                                                                                         // das Key id_of_group bleibt dans unverändert bis wir eine andere anagram Gruppe finden
                
            #endif    
            //index_worked.push_back(i); // nicht notwendig hier. Aber in der for-Scheleife mit j schon,
        }

        for(std::size_t j{i+1}; j<strs_len; j++){
            if(std::find(index_worked.begin(), index_worked.end(), j) != index_worked.end()){ //string an der Stelle i in Vector wurde schon zu einer angram groupe hinzugefügt. Keine Weitere Bearbeitung des gleichen Strings
                continue;
            }
            else{
                if( areAnagram(strs.at(i).data(), strs.at(j).data()) ){
                    anagrammGroups[id_of_group].push_back(strs.at(j)); // das key id_of_group ist die anagram-Gruppe, die gerade ausgefüllt ist
                    index_worked.push_back(j);
                }
            }
        }     
    }

    for( const auto &group : anagrammGroups ){
        std::cout << "Group " << group.first << ":" << std::endl;
        for( const auto &word : group.second ){
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }

#elif(with_set == 1)
    std::set< std::vector<std::string> > anagrammGroups{};
    std::size_t strs_len {strs.size()};
    std::vector<std::size_t> index_worked{};// enthählt Index von String, die schon in anagrammGroups hinzugefügt wurden
    std::vector<std::string> one_group{};

    for(std::size_t i{0}; i<strs_len ; i++ ){
        if(std::find(index_worked.begin(), index_worked.end(), i) != index_worked.end()){ //string an der Stelle i in Vector wurde schon zu einer angram groupe hinzugefügt. Keine Weitere Bearbeitung des gleichen Strings
            continue;
        }
        else{
            one_group.push_back(strs.at(i));
        }

        for(std::size_t j{i+1}; j<strs_len; j++){
            if(std::find(index_worked.begin(), index_worked.end(), j) != index_worked.end()){ //string an der Stelle i in Vector wurde schon zu einer angram groupe hinzugefügt. Keine Weitere Bearbeitung des gleichen Strings
                continue;
            }
            else{
                if( areAnagram(strs.at(i).data(), strs.at(j).data()) ){
                    one_group.push_back(strs.at(j));
                    index_worked.push_back(j);
                }
            }
        } 
        anagrammGroups.insert(one_group);
        one_group.clear();       
    }

    int i{1};
    for( const auto &group : anagrammGroups ){
        std::cout << "Group " << i++ << ":" << std::endl;
        for( const auto &word : group ){
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }

#elif(with_set == 2)
    std::map< std::string, std::vector<std::string> > groups;

    auto wordToKey = [](const std::string &word) -> std::string {
        std::set<char> letterSet; //le set va garder les char dans L'ordre alphabetique. Ainsi tous les caractere d'un mot seront rangé dans l'ordre alphabetique et cela va faciliter la comparaison entre les mots

        for( const auto &letter : word)
            letterSet.insert(letter);

        std::string result;
        for( const auto &letter : letterSet)
            result += letter;

        return result;
    };

    for( const auto &str : strs ){
        const auto key = wordToKey(str); // le mot contenu dans str est mi dans ordre (alphabetique). Ainsi "eat","tea",et "ate" deviendront tous "aet" et seront tous conservé sous la clé "aet" grace a la ligne qui suit
        groups[key].push_back(str);      //  Si la cle n'existe pas encore dans le group, alors wlle serra créé.
    }


    for( const auto &group : groups ){
        std::cout << "Group " << group.first << ":" << std::endl;
        for( const auto &word : group.second ){
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }

#endif  

    auto t2 = std::chrono::high_resolution_clock::now();
    duration_time = t2 - t1;
    std::cout << "Duration = " << duration_time.count()<< std::endl;


    
    


    return 0;
}
