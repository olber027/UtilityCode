//
// Created by molberding on 10/18/2017.
//

#ifndef UTILITYCODE_REGEX_H
#define UTILITYCODE_REGEX_H

#include "SmartString.h"
#include <vector>

using namespace smart_string;

namespace regex {

    template<typename T>
    class Match {
    private:
        SmartString matchingPattern;
        int index;
    public:
        Match(T pattern, int idx) : matchingPattern(pattern), index(idx) {}
        T getPattern() {
            return (T) matchingPattern;
        }
        int getPatternIndex() {
            return index;
        }
    };

    template<typename T>
    class Regex {
    private:

        bool isCompiled;
        SmartString pattern;
        State* initialState;

        //changes characters in the pattern to a more easy to manipulate format.
        SmartString simplify() {

        }

        class State {
        private:
            std::vector<State*> nextPossibleStates;
            SmartString matchingCriteria;
            bool end;
        public:

            std::vector<State*> advance(char c) {
                std::vector<State*> nextStates = std::vector<State*>();
                for(int i = 0; i < nextPossibleStates.size(); i++) {
                    if(nextPossibleStates[i]->matchingCriteria == "" ||
                       nextPossibleStates[i]->matchingCriteria.contains(c)) {
                        nextStates.push_back(nextPossibleStates[i]);
                    }
                }
                return nextStates;
            }

            bool isEnd() {
                return end;
            }
        };

        class PossibleMatch {
        private:
            SmartString currentContents;
            State* currentState;
            int startingIndex;
        public:
            PossibleMatch(SmartString contents, State* state, int index) :
                    currentContents(contents), currentState(state), startingIndex(index) {}
            State* getState() {
                return currentState;
            }
            SmartString getContents() {
                return currentContents;
            }
            int getStartingIndex() {
                return startingIndex;
            }
        };

    public:

        template<typename U>
        void compile(const U& Pattern) {
            pattern = Pattern;
            compile();
        }

        void compile() {

            SmartString str = simplify();

            isCompiled = true;
        }

        template<typename U>
        Match<T> matchOne(const U& text) {
            SmartString str = text;
            std::vector<PossibleMatch> currentPossibleMatches;
            std::vector<PossibleMatch> nextPossibleMatches = std::vector<PossibleMatch>();
            std::vector<Match<T>> matches = std::vector<Match<T>>();

            if(!isCompiled) {
                compile();
            }

            for(int i = 0; i < str.length(); i++) {
                currentPossibleMatches = nextPossibleMatches;
                nextPossibleMatches = std::vector<PossibleMatch>();

                std::vector<State*> nextStates = initialState->advance(str[i]);
                for(int k = 0; k < nextStates.size(); k++) {
                    nextPossibleMatches.push_back(PossibleMatch(str[i], nextStates[k], i));
                }

                for(int j = 0; j < currentPossibleMatches.size(); j++) {
                    PossibleMatch currentMatch = currentPossibleMatches[j];
                    if(currentMatch.getState()->isEnd()) {
                        return Match<T>(currentMatch.getContents(), currentMatch.getStartingIndex());
                    }
                    std::vector<State*> nextStates = currentMatch.getState()->advance(str[i]);
                    for(int k = 0; k < nextStates.size(); k++) {
                        nextPossibleMatches.push_back(
                                PossibleMatch(
                                        currentMatch.getContents().append(str[i]),
                                        nextStates[k],
                                        currentMatch.getStartingIndex()
                                )
                        );
                    }
                }
            }

            for(int i = 0; i < currentPossibleMatches.size(); i++) {
                PossibleMatch currentMatch = currentPossibleMatches[i];
                if(currentMatch.getState()->isEnd()) {
                    return Match<T>(currentMatch.getContents(), currentMatch.getStartingIndex());
                }
            }

            return Match<T>("", -1);
        }

        template<typename U>
        std::vector<Match<T>> match(const U& text) {
            SmartString str = text;
            std::vector<PossibleMatch> currentPossibleMatches;
            std::vector<PossibleMatch> nextPossibleMatches = std::vector<PossibleMatch>();
            std::vector<Match<T>> matches = std::vector<Match<T>>();

            if(!isCompiled) {
                compile();
            }

            for(int i = 0; i < str.length(); i++) {
                currentPossibleMatches = nextPossibleMatches;
                nextPossibleMatches = std::vector<PossibleMatch>();

                std::vector<State*> nextStates = initialState->advance(str[i]);
                for(int k = 0; k < nextStates.size(); k++) {
                    nextPossibleMatches.push_back(PossibleMatch(str[i], nextStates[k], i));
                }


                for(int j = 0; j < currentPossibleMatches.size(); j++) {
                    PossibleMatch currentMatch = currentPossibleMatches[j];
                    if(currentMatch.getState()->isEnd()) {
                        matches.push_back(Match<T>(currentMatch.getContents(), currentMatch.getStartingIndex()));
                        continue;
                    }
                    std::vector<State*> nextStates = currentMatch.getState()->advance(str[i]);
                    for(int k = 0; k < nextStates.size(); k++) {
                        nextPossibleMatches.push_back(
                                PossibleMatch(
                                        currentMatch.getContents().append(str[i]),
                                        nextStates[k],
                                        currentMatch.getStartingIndex()
                                )
                        );
                    }
                }
            }

            for(int i = 0; i < currentPossibleMatches.size(); i++) {
                PossibleMatch currentMatch = currentPossibleMatches[i];
                if(currentMatch.getState()->isEnd()) {
                    matches.push_back(Match<T>(currentMatch.getContents(), currentMatch.getStartingIndex()));
                }
            }

            return matches;
        }
    };

}
#endif //UTILITYCODE_REGEX_H
