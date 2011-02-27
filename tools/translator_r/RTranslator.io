#!/usr/local/bin/io

false asJson := "false"
true asJson := "true"

RTranslator := Object clone do(

jobs := nil
methods := nil
fields := nil
properties := nil
entity := nil

stages := nil
jobFields := nil
messageSlots := nil

defaultStage := nil

jobNameInProcess := nil
jobInProcess := nil

stageInProcess := nil
stageNameInProcess := nil

messageSlotNameInProcess := nil
messageSlotInProcess := nil

methodNameInProcess := nil
methodInProcess := nil

initEntity := method(objectName,
	entity = Map clone
	entity atPut("Методы", methods = Map clone) // SVV!
	entity atPut("Поля", fields = Map clone) // SVV!
	entity atPut("Свойства", properties = Map clone) // SVV!
	entity atPut("Работы", jobs = Map clone) // SVV!
	properties atPut("Имя", objectName) // SVV!
	properties atPut("Идентификаторы", List clone) // SVV!
)

translateJobSignature := method(line,
	line tokens foreach(index, token,
		index switch(
			0,
				if(token isJob,
					jobs atPut(jobNameInProcess = token name, jobInProcess = Map clone)
					jobInProcess atPut("Стадии", stages = Map clone) // SVV!
					jobInProcess atPut("Ожидаемые сообщения", messageSlots = Map clone) // SVV!
					jobInProcess atPut("Поля", jobFields = Map clone), // SVV
				
					RTranslatorError with("Job name in signature is invalid: #{token}" interpolate, line)
				),
			1,
				defaultStage = token,
				
				RTranslatorError with("Job signature is invalid: #{line rawLine}" interpolate, line)
		)
	)
)

translateStageSignature := method(line,
	messageSlotInProcess = Map clone
	messageSlotInProcess atPut("Метод идентификации", identificationMethod := List clone)
	methodInProcess = List clone
	stageInProcess = Map clone
	
	waitingForBinaryOperator := false
	waitingForOperand := false
	parameterToCheck := nil
	binaryOperator := nil
	line tokens foreach(index, token,
		if(waitingForBinaryOperator,
			token switch(
			"=", 
				binaryOperator = "Совпадение" // SVV!
				waitingForBinaryOperator = false
				waitingForOperand = true,
			"*=",
				binaryOperator = "Совпадение с полем" // SVV!
				waitingForBinaryOperator = false
				waitingForOperand = true,				

				RTranslatorError with("Invalid binary operator: #{token}" interpolate, line)
			)
			continue
		)
		if(waitingForOperand,
			identificationMethod append(Map with(
							"Ключ", parameterToCheck,
							"Метод проверки", binaryOperator,
							"Значение", token))
			waitingForOperand = false
			continue
		)
		if(index == 0,
			stageNameInProcess = token
			continue
		)
		if(token isMessageField,
			identificationMethod append(Map with(
							"Ключ", token name,
							"Метод проверки", "Наличие")) // SVV!
			continue
		)
		if(token isField,
			RTranslatorError with("Message field has invalid name: #{token}" interpolate, line)
		)
		parameterToCheck = token
		waitingForBinaryOperator = true
	)
	if(waitingForBinaryOperator or waitingForOperand,
		RTranslatorError with("Incomplete condition.", line)
	)
	
	messageSlotNameInProcess = methodNameInProcess = line tokens clone atInsert(1, " ") join
	methods atPut(methodNameInProcess, Map with("Базовый", false, "Тело", methodInProcess))
	if(messageSlotInProcess at("Метод идентификации") isEmpty,
		stageInProcess atPut("Необходимо сообщений", 0) // SVV!
		stageInProcess atPut("Ожидаемые сообщения", list()), // SVV!
		
		stageInProcess atPut("Необходимо сообщений", 1) // SVV!
		stageInProcess atPut("Ожидаемые сообщения", list(messageSlotNameInProcess)) // SVV!
		messageSlots atPut(messageSlotNameInProcess, messageSlotInProcess)
	)
	stageInProcess atPut("Метод", methodNameInProcess)
	if(stageNameInProcess == defaultStage,
		if(messageSlotInProcess at("Метод идентификации") isEmpty,
			stageInProcess atPut("Состояние", "Готово"),
			stageInProcess atPut("Состояние", "Ожидание")
			messageSlotInProcess atPut("Состояние", "Открыто")
		),
		stageInProcess atPut("Состояние", "Заблокировано")
		messageSlotInProcess atPut("Состояние", "Заблокировано")
	)
	stages atPut(methodNameInProcess, stageInProcess)
)

translateBodyLine := method(line,
	mode := "Starting"
	object := nil
	attributeName := nil
	action := Map clone
	messageInProcess := nil
	line tokens foreach(index, token,
		mode switch(
		"Starting",
			token switch(
			"ВЫХОД",
				mode = "EXIT read"
				action atPut("Действие", "Завершить"), // SVV!
			"ПЕРЕЙТИ",
				mode = "TO reading",
				
				object = token
				mode = "Object read"
			),
		"EXIT read",
			RTranslatorError with("Garbage after keyword ВЫХОД", line),
		"TO reading",
			action atPut("Действие", "Перейти") // SVV!
			action atPut("Имя стадии", token) // SVV!
			mode = "TO read",
		"TO read",
			RTranslatorError with("Garbage after stage name.", line),
		"Object read",
			token switch(
			"+-?",
				messageInProcess = Map clone
				methodInProcess append(Map with("Действие", "Добавить сущность в вершину", "Значение", messageInProcess)) // SVV!
				if(object isField,
					action atPut("Действие", "Послать сообщение объекту из поля") // SVV!
					action atPut("Имя поля", object name) // SVV!
				)
				if(object isMessageField,
					action atPut("Действие", "Послать сообщение объекту из поля сообщения") // SVV!
					action atPut("Имя поля", object name) // SVV!
					action atPut("Имя сообщения", messageSlotNameInProcess) // SVV!
				)
				if(action at("Действие") isNil,
					RTranslatorError with("Message receiver must be some kind of field.", line)
				)
//				action atPut("Сообщение", messageInProcess) // SVV!
				messageInProcess atPut("Тип", "Запрос") // SVV!
				mode = "Reading request",
			"+-.",
				messageInProcess = Map clone
				methodInProcess append(Map with("Действие", "Добавить сущность в вершину", "Значение", messageInProcess)) // SVV!
				if(object isField,
					action atPut("Действие", "Послать сообщение объекту из поля сообщения") // SVV!
					action atPut("Имя поля", object name) // SVV!
				)
				if(object isMessageField,
					action atPut("Действие", "Послать сообщение объекту из поля") // SVV!
					action atPut("Имя поля", object name) // SVV!
					action atPut("Имя сообщения", messageSlotNameInProcess) // SVV!
				)
				if(action at("Действие") isNil,
					RTranslatorError with("Message receiver must be some kind of field.", line)
				)
//				action atPut("Message", messageInProcess) // SVV!
				messageInProcess atPut("Тип", "Ответ") // SVV!
				messageInProcess atPut("Ответ", "Успех") // SVV!
				mode = "Reading request",
			"+-!",
				messageInProcess = Map clone
				methodInProcess append(Map with("Действие", "Добавить сущность в вершину", "Значение", messageInProcess)) // SVV!
				if(object isField,
					action atPut("Действие", "Послать сообщение объекту из поля сообщения") // SVV!
					action atPut("Имя поля", object name) // SVV!
				)
				if(object isMessageField,
					action atPut("Действие", "Послать сообщение объекту из поля") // SVV!
					action atPut("Имя поля", object name) // SVV!
					action atPut("Имя сообщения", messageSlotNameInProcess) // SVV!
				)
				if(action at("Действие") isNil,
					RTranslatorError with("Message receiver must be some kind of field.", line)
				)
//				action atPut("Message", messageInProcess) // SVV!
				messageInProcess atPut("Тип", "Ответ") // SVV!
				messageInProcess atPut("Ответ", "Неудача") // SVV!
				mode = "Reading request",
			"=+",
				action atPut("Действие", "Установить ТВА") // SVV!
				mode = "Set 1",
			":=+",
				action atPut("Действие", "Установить поле объекта") // SVV!
				mode = "Set 1",
			"::=+",
				action atPut("Действие", "Установить глобальное поле") // SVV!
				mode = "Set 1",
			"_=+",
				action atPut("Действие", "Установить поле работы") // SVV!
				mode = "Set 1",

				RTranslatorError with("Invalid operation: #{token}." interpolate, line)
			),
		"Reading request",
			messageInProcess atPut("Запрос", token) // SVV!
			mode = "Reading attribute name",
		"Reading attribute name",
			attributeName = token
			mode = "Reading binary operator",
		"Reading binary operator",
			if(token == "=",
				mode = "Reading attribute value",
				RTranslatorError with("Invalid binary operator: #{token}." interpolate, line)
			),
		"Reading attribute value",
			if(token isField,
				methodInProcess append(Map with("Действие", "Идентификатор поля", "Имя поля", token name))
				methodInProcess append(Map with("Действие", "Добавить сущность в отображение", "Ключ", attributeName)),
			
			if(token isMessageField,
				methodInProcess append(Map with("Действие", "Сущность поля сообщения", "Имя поля", token name))
				methodInProcess append(Map with("Действие", "Добавить сущность в отображение", "Ключ", attributeName)),

				messageInProcess atPut(attributeName, token)
//				methodInProcess append(Map with("Действие", "Добавить сущность в отображение", "Ключ", attributeName, "Значение", token))
			))
			attributeName = nil
			mode = "Reading attribute name",
		"Set 1",
			mode = "Set 2"
			if((token isField) or (token isMessageField),
				RTranslatorError with("Field to set name may not start with name resolution."),
				action atPut("Имя поля", token)
			)
			if((token isField) or (token isMessageField),
				RTranslatorError with("Field to set object must start with name resolution."),
				action atPut("Объект", object)				
			),
		"Set 2",
			RTranslatorError with("Garbage after setting field operation.", line),

			RTranslatorError with("Internal translator error: Invalid state \"#{mode}\" in parser on stage 1" interpolate, line)
		)
	)
	mode switch(
	"EXIT read",
		methodInProcess append(action),
	"TO read",
		methodInProcess append(action),
	"Reading attribute name",
		methodInProcess append(action),
	"Set 1",
		RTranslatorError with("Field name expected.", line),
	"Set 2",
		methodInProcess append(action),
	"Reading request",
		RTranslatorError with("Request name expected.", line),
	"Reading binary operator",
		RTranslatorError with("Operator expected", line),
	"Reading attribute value",
		RTranslatorError with("Attribute value expected", line),
	"Object read",
		RTranslatorError with("Object read, futher operation expected.", line),
		
		RTranslatorError with("Internal translator error: Invalid state \"#{mode}\" in parser on stage 2" interpolate, line)
	)
)

processTO := method(
	methods foreach(_method,
		_method at ("Тело") foreach(methodEntity,
			if(methodEntity at("Действие") == "Перейти",
				_method at ("Тело") remove(methodEntity)
				stages foreach(stageName, stage, 
					if(stageName beginsWithSeq(methodEntity at("Имя стадии") .. " "),
						_method at ("Тело") append(Map with("Действие", "Разблокировать стадию", "Имя стадии", stageName)),
						_method at ("Тело") append(Map with("Действие", "Заблокировать стадию", "Имя стадии", stageName))
					)
				)
				break
			)
		)
	)
)

writeEntityTo := method(file,
	file write(entity asJson asUTF8)
)

if(System args size == 1,
	fileNamesForProcessing := List clone
	Directory clone with("../../externals_sources") files select(file, file name asUCS2 endsWithSeq(".r")) foreach(file, fileNamesForProcessing append(file path))
	outputPrefix := "../../externals/",
	
	fileNamesForProcessing := System args select(index, value, index >= 1)
	fileNamesForProcessing foreach(file,
		if(file asUCS2 endsWithSeq(".r") not,
			RTranslatorError with("Invalid file extension: #{file}" interpolate)
		)
	)
	outputPrefix := ""
)

fileNamesForProcessing foreach(_inputFileName,
	inputFileName := _inputFileName asUTF8
	inputFile := File clone openForReading(inputFileName)
	lines := inputFile readLines
	inputFile close

	outputFileName := inputFileName exclusiveSlice(0, inputFileName size - 2)
	initEntity(outputFileName asUCS2)

	lines foreach(rawLineNumber, rawLine,
		line := RTranslatorLine with(rawLineNumber + 1, rawLine)
		line indent switch(
			0, translateJobSignature(line),
			1, translateStageSignature(line),
			translateBodyLine(line)
		)
	)
	processTO

	outputFile := File clone openForAppending(outputPrefix .. (outputFileName lastPathComponent)) truncateToSize(0)
	writeEntityTo(outputFile)
	outputFile close
)

)

