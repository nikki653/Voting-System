#include <stdio.h>
#include <string.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 5

typedef struct {
    int voterID;
    char password[20];
    int hasVoted;
} Voter;

typedef struct {
    int candidateID;
    char name[50];
    int voteCount;
} Candidate;

Voter voters[MAX_VOTERS];
Candidate candidates[MAX_CANDIDATES];
int totalVoters = 0, totalCandidates = 0;

void initializeSystem() {
    // Initialize voters
    voters[0] = (Voter){1, "pass1", 0};
    voters[1] = (Voter){2, "pass2", 0};
    totalVoters = 2;

    // Initialize candidates
    candidates[0] = (Candidate){1, "Nikki", 0};
    candidates[1] = (Candidate){2, "Bikash", 0};
    totalCandidates = 2;
}

int authenticateVoter(int voterID, char *password) {
    for (int i = 0; i < totalVoters; i++) {
        if (voters[i].voterID == voterID) {
            if (strcmp(voters[i].password, password) == 0) {
                if (voters[i].hasVoted) {
                    printf("You have already voted.\n");
                    return -1;
                }
                return i; // Successful authentication
            } else {
                printf("Invalid password.\n");
                return -1; // Invalid password
            }
        }
    }
    printf("Voter ID not found.\n");
    return -1; // Voter ID not found
}

void castVote(int voterIndex) {
    printf("Candidates:\n");
    for (int i = 0; i < totalCandidates; i++) {
        printf("%d. %s\n", candidates[i].candidateID, candidates[i].name);
    }
    printf("Enter candidate ID to vote: ");
    int choice;
    scanf("%d", &choice);

    for (int i = 0; i < totalCandidates; i++) {
        if (candidates[i].candidateID == choice) {
            candidates[i].voteCount++;
            voters[voterIndex].hasVoted = 1;
            printf("Vote casted successfully.\n");
            return;
        }
    }
    printf("Invalid candidate ID.\n");
}

void showResults() {
    printf("Election Results:\n");
    for (int i = 0; i < totalCandidates; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].voteCount);
    }
}

int main() {
    initializeSystem();
    int choice, voterID;
    char password[20];

    while (1) {
        printf("1. Vote\n2. Show Results\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter voter ID: ");
                scanf("%d", &voterID);
                printf("Enter password: ");
                scanf("%s", password);

                int voterIndex = authenticateVoter(voterID, password);
                if (voterIndex != -1) {
                    castVote(voterIndex);
                }
                break;
            case 2:
                showResults();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}