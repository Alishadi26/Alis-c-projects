import os
from dotenv import load_dotenv
from google import genai

load_dotenv()

client = genai.Client(api_key=os.getenv("GEMINI_API_KEY"))

name = input("Please enter your name to start chatting with our chatbot: ")
print("Please type anything to our chatbot or type 'bye' to exit.")

while True:
    message = input(f"{name}: ")
    if message.lower() in ["bye", "exit", "quit", "goodbye"]:
        print(f"Bot: Goodbye! {name}")
        break

    print("Bot is typing...")
    response = client.models.generate_content(
        model="gemini-3.6-flash",
        contents=message,
    )
    print("Bot:", response.text)