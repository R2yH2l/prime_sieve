import openai
openai.api_key = "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"

prompt = "Once upon a time"
response = openai.Completion.create(
    engine="davinci",
    prompt=prompt,
    max_tokens=50,
    n=1,
    stop=None,
    temperature=0.5,
)

print(response.choices[0].text)