# INFO 3604 - Final Year Project Repository

## Research Project : Ontology-Driven Fake News Detection and Early Warning Systems for Post Disaster Management

Our project's objective was to develop a domain-specific disaster ontology to be incorporated into the Veracity Architecture's compareText algorithm to be utilized in the architecture's fake news detection mechanism. This algorithm operates as a content similarity function within the monitoring agent component (Reporter), and computes a cosine similarity score between the character vectors of the algorithm's news message input and an array of topic-specific keywords. The goal of the ontology is to model disaster event data effectively to replace the keyword array, so that the algorithm computes its similarity score by comparing the input message against an expanded range of disaster concepts.

In addition to creating the disaster ontology, we reviewed the algorithm's similarity score calculation, and enhanced the cosine similarity that was intially done on raw character vectors, to compute the scores on context-aware vectors, using the SBERT or Sentence-BERT model in Python to convert the input message and ontology instances to sentence embeddings that are dense vector representations of a sentence. Using context-aware vectors instead of raw character vectors incorporates a semantic layer into the algorithm's similarity score computation. 

The contents of the folders and files stored in this repository are outlined as follows:

- Similarity_Model : contains the finalized implementation of the ontology in the compareText algorithm. The RDF ontology file is parsed and each instance description is extracted and stored in a JSON file, which the algorithm calls on everytime it is called for comparison. similarity_model.py wraps the algorithm in a class, which is called in the testing notebook. The testing notebook outline the evaluation of the model carried out with a threshold of 0.5 and the test dataset

- codebases : contains the C++ codebase of the compareText algorithm and an initial attempt of the python version of the algorithm. This was an early attempt that was not further utilized in our end product.

- dataset_cleaning : contains the disaster datasets used to populate the ontology and notebooks where cleaning and preprocessing steps were executed to condense and merge the datasets.

- model_testing : contains initial testing of a prediction model on an obtained output dataset from the Veracity architecture, which demonstrates the accuracy of Veracity's prediction utilizing all credibility features.

- ontology_imports : contains the intial exported RDF ontology structure without instances (DisasterOntology.rdf). Imports data from the merged dataset into the ontology and saves the updated, populated version to be used in the algorithm's implementation as disaster_ontology.rdf.

- testings : contains trial tests to determine the final implementation of the similarity score computation. testing_ontology.py uses the Wu-Palmer metric to test the similarity, which did not yield the results we wanted with the similarity score. SBERT_testing.ipynb contains implementation using the SBERT model. We used trial and error with different versions of the code to debug and curate our final implementation of the model.


### Configurations

Each notebook contains the necessary install and import lines for the libraries utilized to run the code. Running these code segments will install and import the libraries on your selected kernel. Once installed, only the code segments containin the import statements will need to be run to utilize the library. disaster_ontology.rdf is duplicated in two folders, as notebooks within those folders call on the file for their operations. Should any errors be encountered running the code, with the file not being found, simply copy this file to the folder containing the code. 

The similarity score for any message can be tested in test.ipynb in the Similarity_Model folder. The following example shows how to use the `SimilarityModel` class to compute semantic similarity between a message and concepts defined in the ontology.

```python
from similarity_model import SimilarityModel

# Load the similarity model with ontology descriptions
model = SimilarityModel("ontology_descriptions.json")

# Compare a message to ontology instances
similarity_score = model.compare_text(message)

print(f"Similarity Score: {similarity_score}")
```

#### Description

- `SimilarityModel`: A class that loads ontology-based descriptions and computes semantic similarity using Sentence-BERT.
- `ontology_descriptions.json`: A JSON file containing descriptions of disaster-related concepts (e.g., types of events, locations).
- `compare_text(message)`: Returns a similarity score indicating how closely the input `message` matches any concept in the ontology.


