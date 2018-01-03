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

        class State {
        private:
            std::vector<State*> nextPossibleStates;
            SmartString matchingCriteria;
            bool end;
        public:

            State() : nextPossibleStates(std::vector<State*>()), matchingCriteria(""), end(false) {}
            template<typename U>
            State(U criteria) : nextPossibleStates(std::vector<State*>()), matchingCriteria(criteria), end(false) {}
            template<typename U>
            State(U criteria, bool End) : nextPossibleStates(std::vector<State*>()), matchingCriteria(criteria), end(End) {}

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

        bool isCompiled;
        SmartString pattern;
        State* initialState;

    public:

        template<typename U>
        void compile(const U& Pattern) {
            pattern = Pattern;
            /*
             *
parse(str)
	parenCount = 0
	index = 0
	strings = []
	currentString = ""
	States = []
	while index < str.size()
		if str[index] == "("
			parenCount++
			currentString += str[index]
		else if str[index] == ")"
			parenCount--
			currentString += str[index]
		else if str[index] == "|" and parenCount <= 0
			strings.add(currentString)
			currentString = ""
		else
			currentString += str[index]
		index++

	for string in strings
		index = 0
		currentStates = []
		while index < string.size()
			resultStates = []
			if string[index] == "("
				parenCount = 0
				index++
				substr = ""
				while string[index] != ")" or parenCount != 0 //not accounting for going off end of string
					substr += string[index]
					if string[index] == "("
						parenCount++
					if string[index] == ")"
						parenCount--
					index++
				resultStates = parse(substr)
			else
				resultStates.add(stringToState(string[index]))

			if currentStates is empty
				for resultState in resultStates
					states.add(resultState)

			for state in currentStates
				for resultState in resultStates
					state.addChild(resultState)
			currentStates = resultStates

	return states
             */
            compile();
        }

        void compile() {

            initialState = new State;
            State* currentState = initialState;


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
