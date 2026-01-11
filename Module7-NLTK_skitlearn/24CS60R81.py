import nltk
import networkx as nx
import matplotlib.pyplot as plt
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity

with open("input_doc.txt","r") as file : 
    text = file.read()
    sentences = sent_tokenize(text)
    words = word_tokenize(text)
    #print(words)

    bigrams = list(nltk.bigrams(words))
    trigrams = list(nltk.trigrams(words))


def remove_stopwords(text):
 # Tokenize the input text
    tokens = word_tokenize(text)

 # Load the stopwords list
    stop_words = set(stopwords.words('english'))

 # Remove stopwords from the tokenized text
    filtered_tokens = [word for word in tokens if
    word.lower() not in stop_words]

 # Join the filtered tokens back into a string
    filtered_text = ' '.join(filtered_tokens)

    return filtered_text

clean_sentences = [remove_stopwords(sentence) for sentence in sentences]


sentence_all = [[sentence] for sentence in sentences]


def generate_tfdf_matrix(filtered_text):
    # create object
    tfidf = TfidfVectorizer()
    # get tf-df values
    result = tfidf.fit_transform(filtered_text)

    tfidf = result.toarray()
    print(tfidf)
    cosine = cosine_similarity(tfidf)
    print(cosine)

    return cosine

cosine = generate_tfdf_matrix(clean_sentences)

G = nx.Graph()

for i in range (len(cosine)):
    for j in range(len(cosine[0])):
        if i!=j:
             G.add_edge(i,j, weight = cosine[i][j])
       
print(cosine.shape)
print(G.number_of_edges())
print(G.number_of_nodes())

nx.draw(G)
plt.show()
#pagerank
def pagerank(G):
    K=5
    score = nx.pagerank(G, weight = 'weight')
   
    ranked_sentence = sorted(score, key = score.get, reverse = True)[:K]
   
    ranked_sentence.sort()
    print(ranked_sentence)
    list_ranked_sentence = [sentences[i] for i in ranked_sentence]

    print()
    print(list_ranked_sentence)
    # output = open("output.txt",'w')
    # output.write('\n' join (list_ranked_sentence))
pagerank(G)     