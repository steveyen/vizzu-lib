//
// Created by bela on 2024.02.29..
//

#ifndef DATAFRAME_OLD2_DATATABLE_H
#define DATAFRAME_OLD2_DATATABLE_H

#include "../impl/dataframe.h"
#include "chart/options/channel.h"

#include "types.h"

namespace Vizzu::Gen
{
class Options;
enum class ChannelId : std::uint8_t;
}

namespace Vizzu::Data
{

class DataCube
{
	struct iterator_t;

public:
	std::shared_ptr<dataframe::dataframe_interface> df;
	std::map<std::pair<std::string, dataframe::aggregator_type>,
	    std::string>
	    measure_names;

	struct DimensionInfo
	{
		std::string name;
		std::span<const std::string> categories;
		std::size_t size{};
		std::size_t ix{};

		[[nodiscard]] bool operator<(const DimensionInfo &other) const
		{
			return name < other.name;
		}

		[[nodiscard]] friend bool operator<(const DimensionInfo &lhs,
		    const SeriesIndex &si)
		{
			return lhs.name < si.getColIndex();
		}

		[[nodiscard]] friend bool operator<(const SeriesIndex &si,
		    const DimensionInfo &rhs)
		{
			return si.getColIndex() < rhs.name;
		}
	};
	Type::UniqueList<DimensionInfo> dim_reindex;

	std::map<Gen::ChannelId,
	    std::shared_ptr<dataframe::dataframe_interface>>
	    cacheImpl;

	DataCube(const DataTable &table, const Gen::Options &options);

	[[nodiscard]] bool empty() const;

	[[nodiscard]] std::shared_ptr<const CellInfo>
	cellInfo(const MultiIndex &index, bool needMarkerInfo) const;

	[[nodiscard]] double aggregateAt(const MultiIndex &multiIndex,
	    const Gen::ChannelId &channelId,
	    const SeriesIndex &seriesId) const;

	[[nodiscard]] double valueAt(const MultiIndex &multiIndex,
	    const SeriesIndex &seriesId) const;

	[[nodiscard]] MarkerId getId(const SeriesList &,
	    const std::optional<std::size_t> &,
	    const MultiIndex &) const;

	[[nodiscard]] std::string joinDimensionValues(
	    const SeriesList &sl,
	    const MultiIndex &index) const;

	[[nodiscard]] const std::string &getName(
	    const SeriesIndex &seriesId) const;

	[[nodiscard]] iterator_t begin() const;
	[[nodiscard]] static iterator_t end();

private:
	struct iterator_t
	{
		const DataCube *parent{};
		MultiIndex index;

		[[nodiscard]] bool operator!=(const iterator_t &other) const;

		void operator++();

		[[nodiscard]] const MultiIndex &operator*() const;
	};

	void check(iterator_t &it) const;
	void incr(iterator_t &it) const;
};

}

#endif // DATAFRAME_OLD2_DATATABLE_H
