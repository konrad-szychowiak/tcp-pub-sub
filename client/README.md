# Client

## Actors
- human: User
- system: Application

## Usage
 
+ User opens the Application
+ Application asks User for the username
+ User gives hers username
+ Application shows options to:
  + view (and read) existing conversations (`-> subscriber`)
  + create a new conversation (`-> publisher`)

### Publishing

+ user selects an option to create a conversation
+ system asks for the [conversation info](#conversation-info)
+ system shows the user 

## Constructs

### Conversation Info
+ (_auto set_) id
+ (_auto set_) creator: username
+ title: string
