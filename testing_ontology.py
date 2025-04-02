from rdflib import Graph
from nltk.corpus import wordnet as wn
import numpy as np

# Load the ontology
g = Graph()
g.parse("disaster_ontology.rdf")  # Replace with your ontology file path

# SPARQL Query to extract disaster event concepts
QUERY = """
PREFIX ex: <http://www.semanticweb.org/zakar/ontologies/2025/1/DisasterOntology#>
SELECT ?event ?subtype WHERE {
    ?event a ex:DisasterEvent ;
           ex:disasterSubtype ?subtype .
}
"""

def wordnet_similarity(word1, word2):
    """Compute Wu-Palmer similarity using WordNet."""
    syn1 = wn.synsets(word1)
    syn2 = wn.synsets(word2)

    if not syn1 or not syn2:
        return 0  # No similarity if words are not in WordNet

    sim_scores = [syn1[0].wup_similarity(s) for s in syn2 if syn1[0].wup_similarity(s)]
    return max(sim_scores) if sim_scores else 0

def compareText(message: str):
    """Compare message text with ontology disaster events."""
    # Tokenize message into words
    message_words = message.lower().split()

    # Fetch disaster event subtypes from ontology
    results = g.query(QUERY)
    ontology_concepts = [str(row.subtype.split("#")[-1]).lower() for row in results]

    similarity_scores = []
    
    for concept in ontology_concepts:
        concept_words = concept.split("_")  # Assume ontology uses snake_case

        # Compute similarity between each word in the message and ontology concept
        sim_values = [wordnet_similarity(word, concept_word) for word in message_words for concept_word in concept_words]

        # Take the max similarity score for this concept
        max_sim = max(sim_values) if sim_values else 0
        similarity_scores.append(max_sim)

    # Normalize the similarity scores (equivalent to Ms in your C++ code)
    if similarity_scores:
        # return np.mean(similarity_scores)
        return max(similarity_scores)
    return 0.0  # No similarity found

# Example usage
message = "Parts of northern Somalia and areas along the Juba and Shabelle River basins in Somalia have experienced heavy rains following the start of the Deyr rains on 7 October."
similarity_score = compareText(message)
print(f"Semantic Similarity Score: {similarity_score:.4f}")

# message = "On 28 October, heavy rains struck the territory of Kalehe in South Kivu, particularly affecting the village of Bushushu. The floods left 3 people missing, more than 50 houses destroyed, and dozens others damaged. In Kindu, district of Maniema, torrential rains caused floodings during the night of 6-7 November. While no casualties have been reported, material damage is considerable on houses, wells, and latrines. More than 3,600 people were made homeless, and many are staying in houses in danger of collapsing. In Tshopo province, an estimated 180,000 people have been affected by floodings since 7 November. More than 17,000 houses have been completely destroyed and thousands more partially. Roads, schools, and sanitary facilities have been severely damaged in Kisangani and in the territories of Isangi and Banalia. Since mid-November 2015, extensive rainfall in the Democratic Republic of Congo (DRC) has led to flooding across the country. On 6 December, the heavy rains led to the overflow of the N'djili River causing flooding in the Debonhome, KingabuaNdanu, KingabuaPécheur and Salongo neighbourhoods of the capital Kinshasa, affecting 10,560 people (2,112 families) and resulting in 31 deaths and numerous injuries. The Processing Centre of the Water Distribution Authority serving Kinshasa along the river N'djili was damaged, reducing the available safe water supply. As of 10 February 2016, the waters had receded in the Debonhomme and Salongo neighbourhoods, however the neighbourhoods of KingabuaPecheur and KingabuaNdanu are still flooded, obliging the population of these two neighbourhoods to use canoes as means of transportation. Other municipalities in Kinshasa have also been affected by the floods, following heavy rains, which have continued throughout January and February, including in Massina, Mont N’Gafula and Ngaliema."
# similarity_score = compareText(message)
# print(f"Semantic Similarity Score: {similarity_score:.4f}")