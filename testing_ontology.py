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
        return np.mean(similarity_scores)
    return 0.0  # No similarity found

# Example usage
message = "Parts of northern Somalia and areas along the Juba and Shabelle River basins in Somalia have experienced heavy rains following the start of the Deyr rains on 7 October."
similarity_score = compareText(message)
print(f"Semantic Similarity Score: {similarity_score:.4f}")