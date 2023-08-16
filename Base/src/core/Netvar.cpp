#include "Netvar.h"
#include "Interfaces.h"

#include <cctype>
#include <string>
#include <format>

void Netvar::Initialize() noexcept
{
	for (auto clientClass = interfaces->client->GetAllClasses(); clientClass; clientClass = clientClass->next)
		if (clientClass->recvTable)
			Netvar::Dump(clientClass->networkName, clientClass->recvTable, 0);
}

void Netvar::Dump(const char* baseClass, RecvTable* table, const std::uint32_t offset)
{
	for (auto i = 0; i < table->propsCount; ++i)
	{
		const auto prop = &table->props[i];

		if (!prop || isdigit(prop->varName[0]))
			continue;

		if (Fnv::Hash(prop->varName) == Fnv::HashConst("baseclass"))
			continue;

		if (prop->recvType == SendPropType::DATATABLE &&
			prop->dataTable &&
			prop->dataTable->tableName[0] == 'D')
			Dump(baseClass, prop->dataTable, std::uint32_t(offset + prop->offset));

		data[Fnv::Hash(std::format("{}->{}", baseClass, prop->varName).data())] =
		{
			prop,
			std::uint32_t(offset + prop->offset)
		};
	}
}

std::uint32_t Netvar::GetOffset(const std::uint32_t hash)
{
	return data.at(hash).offset;
}

RecvProp* Netvar::GetPropN(const std::uint32_t hash)
{
	return data.at(hash).prop;
}
