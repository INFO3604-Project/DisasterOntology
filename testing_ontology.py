from rdflib import Graph, RDFS
from nltk.corpus import wordnet as wn
import random
import datetime
from nltk.tokenize import word_tokenize

class Txc2:
    def __init__(self, ontology_path="DisasterOntology.rdf"):
        self.ontology = Graph()
        self.ontology.parse(ontology_path, format="xml")  # Load ontology
        self.Pc = 3.0  # Trust score
        self.numRatings = 0
        self.numMessages = 0
        self.ratings = []
        self.mRatings = []
    
    def get_ontology_terms(self, concept):
        """Retrieve synonyms for a concept from the ontology and WordNet."""
        synonyms = set()

        # Extract terms from ontology
        for s, p, o in self.ontology.triples((None, RDFS.label, None)):
            if concept.lower() in str(o).lower():
                synonyms.add(str(o))

        # Extract synonyms from WordNet
        for syn in wn.synsets(concept):
            for lemma in syn.lemmas():
                synonyms.add(lemma.name().replace("_", " "))

        return list(synonyms)

    def extract_disaster_terms(self, text):
        """Extract disaster-related words from the text using simple token matching."""
        words = set(word_tokenize(text.lower()))  # Tokenize text and convert to lowercase
        disaster_terms = self.get_ontology_terms("disaster")  # Get disaster-related words
        matched_terms = [word for word in words if word in disaster_terms]  # Find matches
        
        return matched_terms  # Return list of matched disaster-related terms

    def compare_text(self, message):
        """Compare disaster-related words in the message with real events in the ontology."""
        matched_terms = self.extract_disaster_terms(message)
        if not matched_terms:
            return 0.0  # No relevant disaster terms found

        similarity_score = len(matched_terms) / len(message.split())  # Normalize score
        return similarity_score

    def credibility_score(self, ratings):
        """Compute credibility score based on ratings."""
        return sum(ratings) / len(ratings) if ratings else 0.0

    def generate_fake_news(self):
        """Simulate generating fake disaster news."""
        disasters = ["Hurricane", "Earthquake", "Tsunami", "Wildfire", "Flood"]
        locations = ["Florida", "Japan", "India", "California", "Australia"]
        return f"{random.choice(disasters)} hits {random.choice(locations)} causing destruction."

    def generate_real_news(self):
        """Simulate generating real disaster news."""
        return "Hurricane Katrina devastated New Orleans in 2005."

# Example Usage
txc2 = Txc2()

# Fake news detection example
message = "A major earthquake struck California, causing devastation."
similarity_score = txc2.compare_text(message)
print(f"Fake News Similarity Score: {similarity_score:.2f}")  # Higher means closer to real disaster events
