from rdflib.namespace import RDF
from rdflib import Graph, Namespace

g = Graph()
g.parse("disaster_ontology.rdf")

EX = Namespace("http://www.semanticweb.org/zakar/ontologies/2025/1/DisasterOntology#")

event_descriptions = []

for event in g.subjects(RDF.type, EX.DisasterEvent):
    disaster_group = g.value(event, EX.disasterGroup)
    subgroup = g.value(event, EX.disasterSubgroup)
    subtype = g.value(event, EX.disasterSubtype)
    location = g.value(event, EX.ocurredAt)

    country = g.value(location, EX.country) if location else None
    region = g.value(location, EX.region) if location else None
    subregion = g.value(location, EX.subregion) if location else None

    parts = [str(x).lower() for x in [subtype, disaster_group, subgroup, country, region, subregion] if x]
    if parts:
        event_descriptions.append(" ".join(parts))