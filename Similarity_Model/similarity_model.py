import json
from sentence_transformers import SentenceTransformer, util

class SimilarityModel:
    def __init__(self, json_path: str):
        self.instances = json.load(open(json_path, "r"))
        self.model = SentenceTransformer("all-MiniLM-L6-v2")
        self.instance_embeddings = self.model.encode(self.instances, convert_to_tensor=True)


    def preprocess_message(self, msg: str) -> str:
        return msg.strip().lower()

    def compare_text(self, message: str) -> float:
        if not self.instances:
            return 0.0
        message_embedding = self.model.encode(
            self.preprocess_message(message), convert_to_tensor=True
        )
        similarity_scores = util.cos_sim(message_embedding, self.instance_embeddings)
        return float(similarity_scores.max())