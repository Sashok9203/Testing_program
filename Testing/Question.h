#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "QExceptions.h"
#include "mylib.h"
class Question
{
public:
	enum Type
	{
		SINGLE_ANSWER_Q,
		MULTI_ANSWER_Q,
		NO_ANSWER_Q
	};
	static constexpr const char* type_lables[2]
	{
		"<single_answer_q>",
		"<multy_answer_q>",
	};
private:
     static constexpr char question_lable[] = "<question>";
	 static constexpr char answers_lable[]  = "<aswers>";
protected:
	Type type;
	std::string question;
	static const int  questionPoints = 12;
	static const int  blanks = 12;
	void set_question(const std::string& question);
	std::vector<std::string> answersVariants;
	void  addAnswer(const std::string& answer);
	void  delAnswer(const int index);
	void  replaceAnswer(const std::string answer, const int index);
public:
	static constexpr char question_start_label[] = "<q_start>";
	Question(Type type = NO_ANSWER_Q): question("NoQuestion"),type(type) {}
	void setQuestion();
	const std::string& getQuestion() const { return question; }
	const Type& getType() const { return type; }
	std::string getString() const;
	void setAnswerVariant();
	std::string answerVariantToStr() const ;

	virtual void toFStream(std::ofstream& ofs) const;
	virtual void fromFStream(std::ifstream& ifs);
	 
	virtual std::string answerToStr() const = 0;
	virtual int answerToQestion() const = 0;
	virtual void setAnswer() = 0;

};

