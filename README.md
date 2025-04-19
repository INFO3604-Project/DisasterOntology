# INFO 3604 - Final Year Project Repository

## Research Project : Ontology-Driven Fake News Detection and Early Warning Systems for Post Disaster Management

Our project's objective was to develop a domain-specific disaster ontology to be incorporated into the Veracity Architecture's compareText algorithm to be utilized in the architecture's fake news detection mechanism. This algorithm operates as a content similarity function within the monitoring agent component (Reporter), and computes a cosine similarity score between the character vectors of the algorithm's news message input and an array of topic-specific keywords. The goal of the ontology is to model disaster event data effectively to replace the keyword array, so that the algorithm computes its similarity score by comparing the input message against an expanded range of disaster concepts.

In addition to creating the disaster ontology, we reviewed the algorithm's similarity score calculation, and enhanced the cosine similarity that was intially done on raw character vectors, to compute the scores on context-aware vectors, using the SBERT or Sentence-BERT model in Python to convert the input message and ontology instances to sentence embeddings that are dense vector representations of a sentence. Using context-aware vectors instead of raw character vectors incorporates a semantic layer into the algorithm's similarity score computation. 

The contents of the folders and files stored in this repository are outlined as follows:

- Similarity_Model : contains the finalized implementation of the ontology in the compareText algorithm. The RDF ontology file is parsed and each instance description is extracted and stored in a JSON file, which the algorithm calls on everytime it is called for comparison. similarity_model.py wraps the algorithm in a class, which is called in the testing notebook. The testing notebook outline the evaluation of the model carried out with a threshold of 0.5 and the test dataset

- 

